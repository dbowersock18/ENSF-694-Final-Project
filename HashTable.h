#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
using namespace std;

// Generic hash table (2.5 - Fast Building and Resource Lookup).
// Stores pointers keyed by a string (building_id / room_id / etc.) using separate
// chaining with a hand-rolled djb2-style hash function. Doubles its bucket count
// whenever the load factor passes 0.75, so insert/delete/lookup stay O(1) on
// average no matter how many records are stored.
// NOTE: template implementations must live in the header (no matching .cpp) so the
// compiler can instantiate HashTable<Building>, HashTable<Room>, etc. at each use site.
template <typename T>
class HashTable {
public:
    // Default constructor. initialBuckets is kept small and odd to reduce clustering.
    HashTable(int initialBuckets = 101) : bucketCount(initialBuckets), count(0) {
        buckets.assign(bucketCount, nullptr);
    }

    // Deallocates the chain nodes. Does NOT delete the stored T* values - those
    // objects are owned by whoever created them (e.g. Campus::campusBuildings).
    ~HashTable() {
        for (int i = 0; i < bucketCount; i++) {
            Entry* current = buckets[i];
            while (current != nullptr) {
                Entry* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    /*
    * REQUIRES: a key and a pointer to the value it should map to
    * PROMISES: inserts the key/value pair, overwriting the value if the key is already present;
    * triggers a rehash if the load factor exceeds 0.75
    */
    void insert(const string& key, T* value) {
        size_t idx = hashKey(key) % bucketCount;
        Entry* current = buckets[idx];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        buckets[idx] = new Entry(key, value, buckets[idx]);
        count++;
        if (loadFactor() > 0.75) rehash();
    }

    /*
    * REQUIRES: a key
    * PROMISES: removes the entry for that key if present, returning true; returns false otherwise
    */
    bool remove(const string& key) {
        size_t idx = hashKey(key) % bucketCount;
        Entry* current = buckets[idx];
        Entry* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) buckets[idx] = current->next;
                else prev->next = current->next;
                delete current;
                count--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    /*
    * REQUIRES: a key
    * PROMISES: returns the value stored under that key, or nullptr if the key is not present
    */
    T* lookup(const string& key) const {
        size_t idx = hashKey(key) % bucketCount;
        Entry* current = buckets[idx];
        while (current != nullptr) {
            if (current->key == key) return current->value;
            current = current->next;
        }
        return nullptr;
    }

    // Getter for the number of key/value pairs currently stored
    int size() const {
        return count;
    }

    // Getter for the current load factor (size / bucket count), exposed for demo/reporting purposes
    double loadFactor() const {
        return (double) count / bucketCount;
    }

private:
    struct Entry {
        string key;
        T* value;
        Entry* next;
        Entry(const string& k, T* v, Entry* n = nullptr) : key(k), value(v), next(n) {}
    };
    vector<Entry*> buckets;
    int bucketCount;
    int count;

    // djb2-style polynomial rolling hash
    size_t hashKey(const string& key) const {
        size_t hash = 5381;
        for (size_t i = 0; i < key.size(); i++) {
            hash = hash * 33 + (unsigned char) key[i];
        }
        return hash;
    }

    /*
    * PROMISES: doubles the bucket count and reinserts every existing entry, keeping
    * the average chain length (and so average lookup time) bounded as the table grows
    */
    void rehash() {
        int newBucketCount = bucketCount * 2 + 1;
        vector<Entry*> newBuckets(newBucketCount, nullptr);
        for (int i = 0; i < bucketCount; i++) {
            Entry* current = buckets[i];
            while (current != nullptr) {
                Entry* next = current->next;
                size_t idx = hashKey(current->key) % newBucketCount;
                current->next = newBuckets[idx];
                newBuckets[idx] = current;
                current = next;
            }
        }
        buckets = newBuckets;
        bucketCount = newBucketCount;
    }
};

#endif // HASHTABLE_H
