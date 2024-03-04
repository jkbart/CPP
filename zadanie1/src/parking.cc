#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <cctype>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;
using string_it = string::const_iterator;
using parking_time = int;
using word = pair<string_it, string_it>;

enum class Query {
    type_errorQ,
    make_paymentQ,
    check_paymentQ
};

static const parking_time STARTING_TIME =  8 * 60 + 0;
static const parking_time ENDING_TIME   = 20 * 60 + 0;

static const parking_time MIN_PARK_TIME =  0 * 60 + 10;
static const parking_time MAX_PARK_TIME = 11 * 60 + 59;

static int day_parity = 0; 
static unordered_map<string, parking_time> database[2];
static parking_time current_time = 0 * 60 + 0;

static void error_msg(const int line) {
    cerr << "ERROR " << line << "\n";
}

// Funkcja konwertuje czas podany w stringu na parę int-ów (godzina, minuty).
// Funkcja zakłada, że dany string jest poprawną reprezentacją godziny bez białych znaków.
static parking_time string_to_time(const string_it &begin, const string_it &end) {
    int hour = 0;
    int minute = 0;
    string_it i = begin;

    while (*i != '.')
        hour = hour * 10 + *(i++) - '0';

    i++;

    while (i != end)
        minute = minute * 10 + *(i++) - '0';

    return hour * 60 + minute;
}

// Funkcja zwraca iteratory do początku i końca kolejnych wyrazów oddzielonych białymi znakami.
static vector<pair<string_it, string_it>> extract_args(const string &query){
    string_it begin = query.begin();
    string_it end   = query.begin();
    vector<pair<string_it, string_it>> ans;

    while(end != query.end()) {
        if (isspace(*begin)){
            begin++;
            end++;
        }
        else if (!isspace(*end)) {
            end++;
        }
        else {
            ans.push_back({begin, end});
            begin = end;
        }
    }

    if (begin != end)
        ans.push_back({begin, end});

    return ans;
}

// Funkcja zwraca typ zapytania i wektor argumentów.
static pair<Query, vector<pair<string_it, string_it>>> check_query(const string &query) {
    vector<pair<string_it, string_it>> args;
    smatch match;
    static const regex query_pattern("\\s*([A-Z][A-Z0-9]{2,10})(\\s+(?:0?\\d|1\\d|2[0-3])\\.[0-5]\\d)(\\s+(?:0?\\d|1\\d|2[0-3])\\.[0-5]\\d)?\\s*");

    if (!regex_match(query.begin(), query.end(), match, query_pattern))
        return {Query::type_errorQ, {}};
    // Grupa 3 odpowiada za drugą godzinę.
    else if(match[3].matched)
        return {Query::make_paymentQ, extract_args(query)};
    else
        return {Query::check_paymentQ, extract_args(query)};
}

// Funkcja zmienia globalny czas na podany.
static void change_time(parking_time time) {
    // Sprawdzamy, czy zmieniliśmy dzień.
    if (time < current_time) {
        database[day_parity].clear();
        day_parity ^= 1;
    }

    current_time = time;

    return;
}

// Funkcja dodaje dwa czasy do siebie, zakładając, że doba trwa od otwarcia do zamknięcia parkingu.
static parking_time add_time(const parking_time time1, const parking_time time2) {
    parking_time ans = time1 + time2;

    ans = (ans - STARTING_TIME) % (ENDING_TIME - STARTING_TIME) + STARTING_TIME;

    return ans;
}

// Funkcja sprawdza czy czas x mieści się pomiędzy czasami a i b.
static bool is_in_time_interval(const parking_time a, const parking_time b, const parking_time x) {
    if (a <= b && a <= x && x <= b)
        return 1;
    else if (b < a && (a <= x || x <= b)) 
        return 1;
    else
        return 0;
}

// Funkcja obsługuje zapytanie zapłaty za parking.
static void make_payment(const vector<pair<string_it, string_it>> &args, const int line) {
    // number_plate - nazwa tablicy rejestracyjnej
    // query_time   - czas zakupu biletu
    // park_time    - czas do którego został wykupiony bilet
    string number_plate     = string(args[0].first, args[0].second);
    parking_time query_time = string_to_time(args[1].first, args[1].second);
    parking_time park_time  = string_to_time(args[2].first, args[2].second);

    // Sprawdzamy czy argumenty są poprawne.
    if (!is_in_time_interval(STARTING_TIME, ENDING_TIME, query_time) ||
        !is_in_time_interval(STARTING_TIME, ENDING_TIME, park_time) ||
         is_in_time_interval(query_time, add_time(query_time, MIN_PARK_TIME - 1), park_time) ||
        !is_in_time_interval(query_time, add_time(query_time, MAX_PARK_TIME), park_time)) {
        error_msg(line);
        return;
    }

    // Aktualizujemy czas globalny.
    change_time(query_time);

    // Sprawdzamy czy parking został wykupiony do następnego dnia.
    if (park_time < query_time) {
        // Aktualizujemy bazę danych o nowy bilet.
        database[day_parity ^ 1][number_plate] = max(park_time, database[day_parity ^ 1][number_plate]);
        database[day_parity].erase(number_plate);
    }
    else if (!database[day_parity ^ 1].contains(number_plate)) {
        // Aktualizujemy bazę danych o nowy bilet.
        database[day_parity][number_plate] = max(park_time, database[day_parity][number_plate]);
    }

    cout << "OK " << line << "\n";
}

static void check_payment(const vector<pair<string_it, string_it>> &args, const int line) {
    // number_plate - nazwa tablicy rejestracyjnej
    // query_time   - czas zakupu biletu
    string number_plate     = string(args[0].first, args[0].second);
    parking_time query_time = string_to_time(args[1].first, args[1].second);

    // Sprawdzamy czy argumenty są poprawne.
    if (!is_in_time_interval(STARTING_TIME, ENDING_TIME, query_time)) {
        error_msg(line);
        return;
    }

    // Aktualizujemy czas globalny.
    change_time(query_time);

    // Sprawdzamy czy bilet jest ważny.
    if ((database[day_parity].contains(number_plate) && database[day_parity][number_plate] >= query_time) || 
         database[day_parity ^ 1].contains(number_plate)) {
        cout << "YES " << line << "\n";
    }
    else {
        cout << "NO " << line << "\n";
    }
}

int main() {
    string query;
    int line = 0;

    while (getline(cin, query)) {
        ++line;

        pair<Query, vector<pair<string_it, string_it>>> state = check_query(query);

        if (state.first == Query::type_errorQ) {
            error_msg(line);
        }
        else if (state.first == Query::make_paymentQ) {
            make_payment(state.second, line);
        }
        else if (state.first == Query::check_paymentQ) {
            check_payment(state.second, line);
        }
    }
}