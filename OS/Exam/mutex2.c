#include <stdbool.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t lock; /* already initialized */
    int age;
} person;

/* Get one's age */
int get_age(person* p)
{
    pthread_mutex_lock(&p->lock);
    int res= p->age;
    pthread_mutex_unlock(&p->lock);
    return res;
}

/* Increment one's age by one */
void increment_age(person* p)
{
    pthread_mutex_lock(&p->lock);
    p->age++;
    pthread_mutex_unlock(&p->lock);
}

/* Returns true if the person is an adult; otherwise false */
bool is_adult(person* p)
{
    pthread_mutex_lock(&p->lock);
    bool res= get_age(p) >= 20;
    pthread_mutex_unlock(&p->lock);
    return res;
}