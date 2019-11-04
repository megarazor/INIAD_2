typedef int _T;

struct integer{
        _T n;
        struct integer* next;
        struct integer* forward;
};

struct big_integer{
        struct integer *unit;
        struct integer *final;
};

void push(struct big_integer*, _T);

struct big_integer fact(int);

struct big_integer add(struct big_integer, struct big_integer);

void print(struct big_integer);

void big_integer_free(struct big_integer);
