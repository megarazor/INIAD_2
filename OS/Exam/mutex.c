#include <stdbool.h>
#include <pthread.h>

#define HASH_SIZE 256
#define INVALID   (-1)

struct hash {
    pthread_mutex_t mutex; /* already initialized */
    int values[HASH_SIZE];
};

static int hash_index(int value)
{
    return value % HASH_SIZE;
}

/* Returns true on success; false otherwise */
bool hash_append(struct hash* h, int value)
{
    int index = hash_index(value);
    pthread_mutex_lock(&h->mutex);
    if (h->values[index] != INVALID) {
        pthread_mutex_unlock(&h->mutex);
        return false;
    }

    h->values[index] = value;
    pthread_mutex_unlock(&h->mutex);
    return true;
}

void hash_remove(struct hash* h, int value)
{
    int index = hash_index(value);
    pthread_mutex_lock(&h->mutex);
    h->values[index] = INVALID;
    pthread_mutex_unlock(&h->mutex);
}