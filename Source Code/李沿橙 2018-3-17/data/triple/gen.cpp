#include "testlib.h"
#include <cstdio>
#include <cstring>
#include <vector>

static int tot = 0;
static std::vector<std::string> s;

static int al[26];

inline void add_case(const std::string &t)
{
    tot += t.size();
    s.push_back(t);
}

inline void gen_random(int alpha, int len, int noise = 0)
{
    shuffle(al, al + 26);
    std::string t(len, ' ');
    for (int i = 0; i < len; ++i) t[i] = 'a' + al[rnd.next(alpha)];
    for (int i = 0; i < noise; ++i) t[rnd.next(len)] = 'a' + rnd.next(26);
    add_case(t);
}

inline void gen_construct(int alpha, int len, int noise = 0)
{
    shuffle(al, al + 26);
    /*int cyc = rnd.next(2, (int)(sqrt(len) * 4 + 0.5));
    std::string t(len, ' '), o(cyc, ' ');
    if (cyc <= 10) {
        for (int i = 0; i < cyc; ++i) o[i] = 'a' + al[rnd.next(alpha)];
    } else {
        gen_construct(alpha, cyc);
        tot -= s.back().length();
        o = s.back();
        s.pop_back();
    }*/
    int cyc = rnd.next(2, (int)(sqrt(len) / 8 + 0.5));
    std::string t(len, ' '), o(cyc, ' ');
    for (int i = 0; i < cyc; ++i) o[i] = 'a' + al[rnd.next(alpha)];
    char delim = 'a' + al[rnd.next(2)];
    int p = 0, lp = 0, inc = 1;
    while (p < len) {
        switch (lp) {
            case 0: t[p++] = 'a' + al[0]; break;
            case 1: for (int i = 0; p < len && i < cyc; ++i) t[p++] = o[i]; break;
            case 2: t[p++] = delim; break;
            case 3: for (int i = cyc - 1; p < len && i >= 0; --i) t[p++] = o[i]; break;
        }
        lp = (lp + inc) % 4;
        if (rnd.next(30) == 0) inc ^= 2;
    }
    for (int i = 0; i < noise; ++i) t[rnd.next(len)] = 'a' + rnd.next(26);
    add_case(t);
}

inline void gen_long(int alpha, int len)
{
    shuffle(al, al + 26);
    int cyc = rnd.next(len / 4, (len - 4) / 3);
    int l_ext = rnd.next(0, len - cyc * 3 - 4);
    std::string t(len, ' '), o(cyc, ' ');
    for (int i = 0; i < cyc; ++i) o[i] = 'a' + al[rnd.next(alpha)];
    for (int i = 0; i < l_ext; ++i) t[i] = 'a' + al[rnd.next(alpha)];
    char delim = 'a' + al[rnd.next(2)];
    int p = l_ext;
    t[p++] = 'a' + al[0];
    for (int i = 0; i < cyc; ++i) t[p++] = o[i];
    t[p++] = delim;
    for (int i = cyc - 1; i >= 0; --i) t[p++] = o[i];
    t[p++] = 'a' + al[0];
    for (int i = 0; i < cyc; ++i) t[p++] = o[i];
    t[p++] = delim;
    while (p < len) t[p++] = 'a' + al[rnd.next(alpha)];
    add_case(t);
}

inline void gen_period(int p, int len, int noise = 0)
{
    shuffle(al, al + 26);
    std::string t(len, ' '), o(p, ' ');
    for (int i = 0; i < p; ++i) o[i] = 'a' + al[rnd.next(p)];
    if (noise > 0 && p == 3) o[2] = o[0];   // OwO
    for (int i = 0; i < len; ++i) t[i] = o[i % p];
    for (int i = 0; i < noise; ++i) t[rnd.wnext(len, rnd.next(2) ? -8 : 8)] = 'a' + rnd.next(26);
    add_case(t);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("%s <case_num>\n", argv[0]);
        return 1;
    }

    registerGen(argc, argv, 1);
    int case_num = (int)strtol(argv[1], NULL, 10);
    for (int i = 0; i < 26; ++i) al[i] = i;

    switch (case_num) {
        case 1:
            add_case("aba");
            add_case("ququ");
            add_case("yjqqqaq");
            add_case("aaaaaaabccbaabcaaaaaa");
            add_case("ababcbabccbaabc");
            add_case("z");
            add_case("aaaaaaaeaaaeaaaeaaaeaaaeaeaeaea");
            for (int i = 0; i < 5; ++i) gen_random(1, 20, 1);
            for (int i = 0; i < 10; ++i) gen_random(2, 10);
            for (int i = 0; i < 9; ++i) gen_random(3, 30);
            gen_random(3, 200, 10);
            gen_random(1, 200, 2);
            gen_random(4, 1000 - tot, 1);
            break;
        case 2: case 3: case 5: case 6: {
            int per, max, sum;
            per = (case_num == 2 || case_num == 5) ? 2 : 3;
            max = (case_num <= 3) ? 1000 : 2e5;
            sum = (case_num <= 3) ? 20000 : 1e6;
            for (int i = 1; i <= 10; ++i) gen_period(per, i);
            for (int i = 0; i < 3; ++i) gen_period(per, max);
            while (tot + 10 < sum) gen_period(per, rnd.wnext(10, std::min(sum - tot, max), 5));
            gen_period(per, sum - tot);
            break;
        }
        case 4:
            gen_random(1, 1000, 2);
            for (int i = 0; i < 5; ++i) gen_random(1, rnd.next(980, 1000), rnd.next(10, 50));
            for (int i = 0; i < 5; ++i) gen_random(2, rnd.next(980, 1000), rnd.next(10, 50));
            for (int i = 0; i < 4; ++i) gen_construct(i * 2 + 20, rnd.next(980, 1000), rnd.next(2));
            for (int i = 0; i < 3; ++i) gen_long(i + 12, rnd.next(980, 1000));
            gen_construct(15, 1000);
            gen_long(10, 1000);
            gen_random(5, 20000 - tot);
            break;
        case 7: case 8: case 9: case 10: {
            int max, sum;
            if (case_num == 7) max = 3e4, sum = 4e5;
            else if (case_num == 8) max = 5e4, sum = 4e5;
            else if (case_num == 9) max = 1e5, sum = 1e6;
            else if (case_num == 10) max = 2e5, sum = 1e6;
            if (case_num == 7) gen_random(1, max);
            if (case_num != 10) gen_random(1, max, 1);
            if (case_num == 8) gen_period(2, max, 2); else gen_random(1, max, 5);
            if (case_num <= 8) gen_period(2, max, 4); else gen_random(2, rnd.next(max - 100, max), 10);
            gen_construct(6, rnd.next(max - 100, max), 1);
            gen_period(2, max, 5);
            gen_long(5, rnd.next(max - 100, max));
            if (tot + max < sum)
                for (int i = 0; i < 2; ++i) gen_construct(i + 14, max / 2 - rnd.next(10), rnd.next(2));
            //if (tot + max < sum)
            //    gen_period(2, max, 3);
            if (tot + max < sum)
                gen_period(2, max, 1);
            if (tot + 2 * max < sum)
                for (int i = 0; i < 4; ++i) gen_period(2 + (i & 1), max / 2 - rnd.next(10), rnd.next(10));
            while (tot + max <= sum) gen_period(2, rnd.next(max - 100, max), 12);
            gen_random(4, sum - tot);
            break;
        }
        default:
            puts("<case_num> should be between 1 and 10 inclusive.");
            return 1;
    }

    printf("%lu\n", s.size());
    shuffle(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++i) puts(s[i].c_str());
    fprintf(stderr, "%lu case(s), %d character(s)\n", s.size(), tot);

    return 0;
}
