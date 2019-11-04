struct fraction{
    int numer;
    int denom;
};

struct fraction add(struct fraction a, struct fraction b);
struct fraction subs(struct fraction a, struct fraction b);
struct fraction mul(struct fraction a, struct fraction b);
struct fraction div(struct fraction a, struct fraction b);
struct fraction reduce(struct fraction f);
void print(struct fraction a);
