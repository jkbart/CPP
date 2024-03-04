#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <string>
#include "poset.h"

namespace {
#define PRINT_VALUE(v) (v == NULL ? "NULL" : "\"" + (string)v + "\"")

#ifndef NDEBUG 
    static constexpr bool debug = true;
#else
    static constexpr bool debug = false;
#endif

    using namespace std;

    // node_t              - typ używany do reprezentacji wierzchołka grafu.
    // Wierzchołek jest reprezentowany jako pointer na nazwę wierzchołka w set_of_node_names_t, 
    // a nie jako iterator, ze względu na to, że iterator nie ma dostępnej funkcji haszującej do unordered_set/map. 
    // poset_id_t          - typ używany do reprezentacji id posetu.
    // set_of_nodes_t      - typ przechowujący zbiór wierzchołków grafu.
    // set_of_node_names_t - typ przechowujący zbiów nazw wierzchołków grafu.
    // node_relations_t    - typ przechowujący relacje wchodzące i wychodzące z danego wierzchołka.
    // id_to_relations_t   - typ przchowujący relacje wszystkich wierzchołków grafu.
    // poset_data_t        - typ przechowujący wszystkie relacje i nazwy wierzchołków danego posetu.
    // id_to_poset_data_t  - typ przechowujący dane różnych posetów.
    using node_t                           = const string*;
    using poset_id_t                       = unsigned long;
    using set_of_nodes_t                   = unordered_set<node_t>;
    using set_of_node_names_t              = unordered_set<string>;
    using node_relations_t                 = pair<set_of_nodes_t,
                                                  set_of_nodes_t>;
    static constexpr int IN                = 0;
    static constexpr int OUT               = 1;
    using id_to_relations_t                = unordered_map<node_t,
                                                           node_relations_t>;
    using poset_data_t                     = tuple<set_of_node_names_t,
                                                   id_to_relations_t>;
    static constexpr int SET_OF_NODE_NAMES = 0;
    static constexpr int ID_TO_RELATIONS   = 1;
    using id_to_poset_data_t               = unordered_map<poset_id_t,
                                                           poset_data_t>;

    // Struktura trzymająca następny wolny numer id posetu.
    poset_id_t& next_free_id() {
        static poset_id_t next_free_id_s;
        return next_free_id_s;
    }

    // Struktura trzymająca dane wszystkich posetów.
    id_to_poset_data_t& id_to_poset_data() {
        static id_to_poset_data_t id_to_poset_data;
        return id_to_poset_data;
    }

    void init_ios() {
        static bool is_init = false;
        if(!is_init) {
            is_init = true;
            ios_base::Init();
        }
    }
}

poset_id_t ::cxx::poset_new(void) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_new()\n";
    }

    id_to_poset_data().insert({next_free_id(), {}});

    if constexpr (debug)
        cerr << "poset_new: poset " << next_free_id() << " created\n";

    return next_free_id()++;
}

void ::cxx::poset_delete(poset_id_t id) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_delete(" << id << ")\n";
    }

    auto poset_it = id_to_poset_data().find(id);

    // Sprawdza, czy poset o danym indeksie istnieje.
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_delete: poset " << id << " does not exist\n";
        return;
    }

    id_to_poset_data().erase(poset_it);

    if constexpr (debug)
        cerr << "poset_delete: poset " << id << " deleted\n";

    return;
}

size_t ::cxx::poset_size(poset_id_t id) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_size(" << id << ")\n";
    }

    auto poset_it = id_to_poset_data().find(id);

    // Sprawdza, czy poset o danym indeksie istnieje.
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_size: poset " << id << " does not exist\n";

        return (size_t) 0;
    }

    int answer = get<SET_OF_NODE_NAMES>(poset_it->second).size();

    if constexpr (debug)
        cerr << "poset_size: poset " << id << " contains " << answer << " element(s)\n";

    return answer;
}

bool ::cxx::poset_insert(poset_id_t id, char const *value) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_insert(" << id <<", " << PRINT_VALUE(value) << ")\n";
    }

    if (value == NULL) {
        if constexpr (debug)
            cerr << "poset_insert: invalid value (NULL)\n";
        return false;
    }

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_insert: poset " << id << " does not exist\n";
        return false;
    }

    // Sprawdza, czy element istnieje już w poset'cie.
    auto node_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value);
    if (node_it != get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug) 
            cerr << "poset_insert: poset " << id <<", element \"" << value << "\" already exists\n";
        return false;
    }

    node_t node = &(*get<SET_OF_NODE_NAMES>(poset_it->second).insert(value).first);

    // Tylko inicjuje wierzchołek.
    get<ID_TO_RELATIONS>(poset_it->second)[node];

    if constexpr (debug) 
        cerr << "poset_insert: poset " << id <<", element \"" << value << "\" inserted\n";
    return true;
}

bool ::cxx::poset_remove(poset_id_t id, char const *value) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_remove(" << id <<", " << PRINT_VALUE(value) << ")\n";
    }
    if (value == NULL) {
        if constexpr (debug)
            cerr << "poset_remove: invalid value (NULL)\n";
        return false;
    }

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug) 
            cerr << "poset_remove: poset " << id <<" does not exist\n";
        return false;
    }

    // Sprawdza, czy usuwany element nie istnieje w poset'cie.
    auto node_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value);
    if (node_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug) 
            cerr << "poset_remove: poset " << id <<", element \"" << value << "\" does not exist\n";
        return false;
    }


    node_t node = &(*node_it);

    // Usuwa wszystkie relację z innymi wierzchołkami.
    auto relations_it = get<ID_TO_RELATIONS>(poset_it->second).find(node);
    for (node_t e : get<IN>(relations_it->second))
        get<OUT>(get<ID_TO_RELATIONS>(poset_it->second)[e]).erase(node);

    for (node_t e : get<OUT>(relations_it->second))
        get<IN>(get<ID_TO_RELATIONS>(poset_it->second)[e]).erase(node);

    // Usuwa element.
    get<ID_TO_RELATIONS>(poset_it->second).erase(node);
    get<SET_OF_NODE_NAMES>(poset_it->second).erase(*node);

    if constexpr (debug) 
        cerr << "poset_remove: poset " << id <<", element \"" << value << "\" removed\n";
    return true;
}

bool ::cxx::poset_add(poset_id_t id, char const *value1, char const *value2) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_add(" << id <<", " << PRINT_VALUE(value1) << ", " << PRINT_VALUE(value2) << ")\n";
    }

    if (value1 == NULL)
        if constexpr (debug) 
            cerr << "poset_add: invalid value1 (NULL)\n";

    if (value2 == NULL)
        if constexpr (debug) 
            cerr << "poset_add: invalid value2 (NULL)\n";

    if (value1 == NULL || value2 == NULL)
        return false;

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_add: poset " << id <<" does not exist\n";
        return false;
    }

    // Sprawdza, czy value1 jest elementem w poset'cie.
    auto node1_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value1);
    if (node1_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_add: poset " << id << ", element \"" << value1 << "\" does not exist\n";
        return false;
    }

    // Sprawdza, czy value1 jest elementem w poset'cie.
    auto node2_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value2);
    if (node2_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_add: poset " << id << ", element \"" << value2 << "\" does not exist\n";
        return false;
    }

    node_t node1 = &(*node1_it);
    node_t node2 = &(*node2_it);

    // Sprawdza, czy już istnieje relacja pomiędzy value1 i value2.
    // relations1/2_it - iterator na wszystkie relacje value1/value2.
    auto relations1_it = get<ID_TO_RELATIONS>(poset_it->second).find(node1);
    auto relations2_it = get<ID_TO_RELATIONS>(poset_it->second).find(node2);
    if (get<IN>(relations1_it->second).find(node2) != get<IN>(relations1_it->second).end() ||
        get<IN>(relations2_it->second).find(node1) != get<IN>(relations2_it->second).end() ||
        node1 == node2) {
        if constexpr (debug)
            cerr << "poset_add: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") cannot be added\n";
        return false;
    }

    // Dodaje relację pomiędzy value1 i value2 tak, że dodaje również zależność
    // pomiędzy wszystkimi już istniejącymi relacjami z value1 i value2.
    get<OUT>(relations1_it->second).insert(node2);
    get<IN>(relations2_it->second).insert(node1);

    for (node_t e : get<IN>(relations1_it->second)) {
        get<OUT>(get<ID_TO_RELATIONS>(poset_it->second)[e]).insert(node2);
        get<IN>(relations2_it->second).insert(e);
    }

    for (node_t e1 : get<OUT>(relations2_it->second)) {
        auto relations3_it = get<ID_TO_RELATIONS>(poset_it->second).find(e1);
        get<IN>(relations3_it->second).insert(node1);
        get<OUT>(relations1_it->second).insert(e1);

        for (node_t e2 : get<IN>(relations1_it->second)) {
            get<OUT>(get<ID_TO_RELATIONS>(poset_it->second)[e2]).insert(e1);
            get<IN>((relations3_it->second)).insert(e2);
        }
    }

    if constexpr (debug)
        cerr << "poset_add: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") added\n";

    return true;
}

bool ::cxx::poset_del(poset_id_t id, char const *value1, char const *value2) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_del(" << id <<", " << PRINT_VALUE(value1) << ", " << PRINT_VALUE(value2) << ")\n";
    }

    if (value1 == NULL)
        if constexpr (debug) 
            cerr << "poset_del: invalid value1 (NULL)\n";

    if (value2 == NULL)
        if constexpr (debug) 
            cerr << "poset_del: invalid value2 (NULL)\n";

    if (value1 == NULL || value2 == NULL)
        return false;

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_del: poset " << id <<" does not exist\n";
        return false;
    }

    // Sprawdza, czy value1 należy do posetu.
    auto node1_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value1);
    if (node1_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_del: poset " << id << ", element \"" << value1 << "\" does not exist\n";
        return false;
    }

    // Sprawdza, czy value2 należy do posetu.
    auto node2_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value2);
    if (node2_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_del: poset " << id << ", element \"" << value2 << "\" does not exist\n";
        return false;
    }

    node_t node1 = &(*node1_it);
    node_t node2 = &(*node2_it);

    // relations1/2_it - iterator na wszystkie relacje value1/value2.
    auto relations1_it = get<ID_TO_RELATIONS>(poset_it->second).find(node1);
    auto relations2_it = get<ID_TO_RELATIONS>(poset_it->second).find(node2);

    // Sprawdza, czy istnieje relacja pomiędzy value1 i value2.
    auto it_to_remove = get<OUT>(relations1_it->second).find(node2);
    if (it_to_remove == get<OUT>(relations1_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_del: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") cannot be deleted\n";
        return false;
    }

    // Sprawdza, czy istnieją pomiędzy value1 i value2 jakieś inne elementy posetu.
    for (node_t e : get<OUT>(relations1_it->second)) {
        if (get<IN>(relations2_it->second).find(e) != get<IN>(relations2_it->second).end()) {
            if constexpr (debug)
                cerr << "poset_del: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") cannot be deleted\n";
            return false;
        }
    }

    // Usuwa relację pomiędzy oboma elementami.
    get<OUT>(relations1_it->second).erase(it_to_remove);
    get<IN>(relations2_it->second).erase(node1);

    if constexpr (debug)
        cerr << "poset_del: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") deleted\n";
    return true;
}

bool ::cxx::poset_test(poset_id_t id, char const *value1, char const *value2) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_test(" << id <<", " << PRINT_VALUE(value1) << ", " << PRINT_VALUE(value2) << ")\n";
    }

    if (value1 == NULL)
        if constexpr (debug) 
            cerr << "poset_test: invalid value1 (NULL)\n";

    if (value2 == NULL)
        if constexpr (debug) 
            cerr << "poset_test: invalid value2 (NULL)\n";

    if (value1 == NULL || value2 == NULL)
        return false;

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_test: poset " << id << " does not exist\n";
        return false;
    }

    // Sprawdza, czy value1 należy do posetu.
    auto node1_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value1);
    if (node1_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_test: poset " << id << ", element \"" << value1 << "\" does not exist\n";
        return false;
    }

    // Sprawdza, czy value2 należy do posetu.
    auto node2_it = get<SET_OF_NODE_NAMES>(poset_it->second).find(value2);
    if (node2_it == get<SET_OF_NODE_NAMES>(poset_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_test: poset " << id << ", element \"" << value2 << "\" does not exist\n";
        return false;
    }

    node_t node1 = &(*node1_it);
    node_t node2 = &(*node2_it);

    if (node1 == node2) {
        if constexpr (debug)
            cerr << "poset_test: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") exists\n";
        return true;
    }

    // relations1_it - iterator na wszystkie relacje value1.
    auto relations1_it = get<ID_TO_RELATIONS>(poset_it->second).find(node1);

    if (get<OUT>(relations1_it->second).find(node2) == get<OUT>(relations1_it->second).end()) {
        if constexpr (debug)
            cerr << "poset_test: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") does not exist\n";
        return false;
    }

    if constexpr (debug)
        cerr << "poset_test: poset " << id << ", relation (\"" << value1 << "\", \"" << value2 << "\") exists\n";
    return true;
}

void ::cxx::poset_clear(poset_id_t id) {
    if constexpr (debug) {
        init_ios();
        cerr << "poset_clear(" << id << ")\n";
    }

    // Sprawdza, czy poset o danym indeksie istnieje.
    auto poset_it = id_to_poset_data().find(id);
    if (poset_it == id_to_poset_data().end()) {
        if constexpr (debug)
            cerr << "poset_clear: poset " << id << " does not exist\n";
        return ;
    }
    
    // Czyści dany poset.
    get<ID_TO_RELATIONS>(poset_it->second).clear();
    get<SET_OF_NODE_NAMES>(poset_it->second).clear();

    if constexpr (debug)
        cerr << "poset_clear: poset " << id << " cleared\n";
    return;
}
