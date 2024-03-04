#ifndef COLLEGE
#define COLLEGE

#include <algorithm>
#include <map>
#include <memory>
#include <ranges>
#include <regex>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

class Course;
class Person;
class Student;
class Teacher;
class PhDStudent;
class College;

namespace college_namespace {
template <typename T> constexpr bool is_college_person = false;
template <>
constexpr inline bool is_college_person<Student> = true; // removing inline leads to clang warning
template <> constexpr inline bool is_college_person<Teacher> = true;
template <> constexpr inline bool is_college_person<PhDStudent> = true;

template <typename T>
concept College_person = requires { is_college_person<T>; };

template <typename T> constexpr bool is_person = is_college_person<T>;
template <> constexpr inline bool is_person<Person> = true;

template <typename T>
concept Person_type = requires { is_person<T>; };
} // namespace college_namespace

class Person {
    private:
        std::string name, surname;

    public:
        Person(const std::string &_name, const std::string &_surname)
            : name(_name), surname(_surname) {}

        virtual ~Person() noexcept {}

        const std::string &get_name() const noexcept {
            return name;
        }

        const std::string &get_surname() const noexcept {
            return surname;
        }

        template <college_namespace::Person_type T> class person_pointer_compare {
            public:
                bool operator()(const std::shared_ptr<T> &l,
                                const std::shared_ptr<T> &r) const noexcept {
                    if (l->get_surname() == r->get_surname()) {
                        return l->get_name() < r->get_name();
                    }
                    return l->get_surname() < r->get_surname();
                }
        };

        template <typename T>
        using container_t = std::set<std::shared_ptr<T>, person_pointer_compare<T>>;
};

class Course {
    public:
        using student_container_t = Person::container_t<Student>;
        using teacher_container_t = Person::container_t<Teacher>;

    private:
        std::string name;
        bool active;

    public:
        Course(const std::string &_name, bool _active = true) : name(_name), active(_active) {}

        const std::string &get_name() const noexcept {
            return name;
        }

        bool is_active() const noexcept {
            return active;
        }

        void set_activity(bool _active) noexcept {
            active = _active;
        }

        class course_pointer_compare {
            public:
                bool operator()(const std::shared_ptr<Course> &l,
                                const std::shared_ptr<Course> &r) const noexcept {
                    return l->get_name() < r->get_name();
                }
        };

        using course_container_t =
            std::set<std::shared_ptr<Course>, Course::course_pointer_compare>;
};

class Student : public virtual Person {
    private:
        bool active;
        Course::course_container_t course_container = {};

    public:
        Student(const std::string &_name, const std::string &_surname, bool _active = true)
            : Person(_name, _surname), active(_active) {}

        virtual ~Student() noexcept {}

        bool is_active() const noexcept {
            return active;
        }

        bool add_studied_course(const std::shared_ptr<Course> &course) {
            auto [iter, was_emplaced] = course_container.emplace(course);
            return was_emplaced;
        }

        const Course::course_container_t &get_courses() const noexcept {
            return course_container;
        }

        void set_activity(bool _active) noexcept {
            active = _active;
        }
};

class Teacher : public virtual Person {
    private:
        Course::course_container_t course_container = {};

    public:
        Teacher(const std::string &_name, const std::string &_surname) : Person(_name, _surname) {}

        virtual ~Teacher() noexcept {}

        bool add_taught_course(const std::shared_ptr<Course> &course) {
            auto [iter, was_emplaced] = course_container.emplace(course);
            return was_emplaced;
        }

        const Course::course_container_t &get_courses() const noexcept {
            return course_container;
        }
};

class PhDStudent : public Student, public Teacher {
    public:
        PhDStudent(const std::string &_name, const std::string &_surname, bool _active = true)
            : Person(_name, _surname), Student(_name, _surname, _active), Teacher(_name, _surname) {
        }
};

namespace college_namespace {
template <typename T>
concept Student_or_teacher = std::is_same_v<T, Teacher> || std::is_same_v<T, Student>;
} // namespace college_namespace

class College {
    public:
        using person_container_t = Person::container_t<Person>;
        using student_container_t = Person::container_t<Student>;
        using phd_student_container_t = Person::container_t<PhDStudent>;
        using teacher_container_t = Person::container_t<Teacher>;

        bool add_course(const std::string &name, bool active = true) {
            auto [iter, was_emplaced] =
                course_container.emplace(std::make_shared<Course>(name, active));
            return was_emplaced;
        }

        auto find_courses(const std::string &pattern) const {
            auto rg =
                course_container | std::views::filter([&](const std::shared_ptr<Course> &crs) {
                    return does_match_pattern(crs->get_name(), pattern);
                });
            return std::vector(rg.begin(), rg.end());
        }

        bool change_course_activeness(const std::shared_ptr<Course> &course, bool active) {
            auto iter = course_container.find(course);
            if (iter == course_container.end() || (*iter) != course) {
                return false;
            }
            (*iter)->set_activity(active);
            return true;
        }

        bool remove_course(const std::shared_ptr<Course> &course) {
            auto iter = course_container.find(course);
            if (iter == course_container.end() || (*iter) != course) {
                return false;
            }
            (*iter)->set_activity(false);
            course_container.erase(iter);
            return true;
        }

        template <college_namespace::College_person T>
        bool add_person(const std::string &name, const std::string &surname, bool active = true) {
            std::shared_ptr<T> ptr;
            if constexpr (std::is_same_v<T, Teacher>) {
                ptr = std::make_shared<Teacher>(name, surname);
            } else {
                ptr = std::make_shared<T>(name, surname, active);
            }
            auto [iter, was_emplaced] = std::get<person_container_t>(containers).emplace(ptr);
            if (!was_emplaced) {
                return false;
            }
            std::get<Person::container_t<T>>(containers).emplace(ptr);
            if constexpr (std::is_same_v<T, PhDStudent>) {
                std::get<teacher_container_t>(containers).emplace(ptr);
                std::get<student_container_t>(containers).emplace(ptr);
            }
            return true;
        }

        bool change_student_activeness(const std::shared_ptr<Student> &student, bool active) {
            auto &students = std::get<student_container_t>(containers);
            auto iter = students.find(student);
            if (iter == students.end() || (*iter) != student) {
                return false;
            }
            (*iter)->set_activity(active);
            return true;
        }

        template <college_namespace::Person_type T>
        auto find(const std::string &name_pattern, const std::string &surname_pattern) const {
            auto rg = std::get<Person::container_t<T>>(containers)
                      | std::views::filter([&](const std::shared_ptr<T> &ptr) {
                            return does_match_pattern(ptr->get_name(), name_pattern)
                                   && does_match_pattern(ptr->get_surname(), surname_pattern);
                        });
            return std::vector(rg.begin(), rg.end());
        }

        template <college_namespace::Student_or_teacher T>
        auto find(const std::shared_ptr<Course> &course) const {
            if constexpr (std::is_same_v<T, Student>) {
                auto course_iter = map_course_to_students.find(course);
                if (course_iter == map_course_to_students.end() || course_iter->first != course) {
                    return student_container_t();
                }
                return course_iter->second;
            } else {
                auto course_iter = map_course_to_teachers.find(course);
                if (course_iter == map_course_to_teachers.end() || course_iter->first != course) {
                    return teacher_container_t();
                }
                return course_iter->second;
            }
        }

        template <college_namespace::Student_or_teacher T>
        bool assign_course(const std::shared_ptr<T> &person,
                           const std::shared_ptr<Course> &course) {
            auto course_iter = course_container.find(course);
            if (course_iter == course_container.end() || (*course_iter) != course) {
                throw std::invalid_argument("Non-existing course.");
            }
            if ((*course_iter)->is_active() == false) {
                throw std::invalid_argument("Incorrect operation on an inactive course.");
            }

            auto &person_container = std::get<Person::container_t<T>>(containers);
            auto person_iter = person_container.find(person);
            if (person_iter == person_container.end() || (*person_iter) != person) {
                throw std::invalid_argument("Non-existing person.");
            }

            if constexpr (std::is_same_v<T, Student>) {
                if ((*person_iter)->is_active() == false) {
                    throw std::invalid_argument("Incorrect operation for an inactive student.");
                }
                person->add_studied_course(course);
                auto [emplaced_iter, was_emplaced] = map_course_to_students[course].emplace(person);
                return was_emplaced;
            } else {
                person->add_taught_course(course);
                auto [emplaced_iter, was_emplaced] = map_course_to_teachers[course].emplace(person);
                return was_emplaced;
            }
        }

    private:
        Course::course_container_t course_container = {};
        std::tuple<person_container_t, student_container_t, phd_student_container_t,
                   teacher_container_t>
            containers = {};
        std::map<std::shared_ptr<Course>, teacher_container_t,
                 Course::course_pointer_compare>
            map_course_to_teachers = {};
        std::map<std::shared_ptr<Course>, student_container_t,
                 Course::course_pointer_compare>
            map_course_to_students = {};

        bool does_match_pattern(const std::string &str, const std::string &pattern) const {
            static const std::regex single_char("\\?");
            static const std::regex any_seq("\\*");

            const std::string pattern_cpy_1 = std::regex_replace(pattern, single_char, ".");

            const std::string pattern_cpy_2 = std::regex_replace(pattern_cpy_1, any_seq, ".*");

            const std::regex regex_pattern(pattern_cpy_2);

            std::smatch temp;

            return std::regex_match(str, temp, regex_pattern);
        }
};

#endif // COLLEGE
