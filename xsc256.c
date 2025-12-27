#include <xsc256.h>

int192 x_box(int128 input)
{
    int192 output;
    int256 *p;

    output.x = 0;

    p = (int256 *)&output;
    *p = $32((int192)(0 | input));

    return output;
}

// int192 s_boxes(int192 input){
//     int8 w[24], w_;
//     int192 *p;
//     int192 input_;
//     int192 output; //42 minute
//     int8 x,a;
//     semiwords in,out;

//     input_ = input;
//     p = &input_;

//     for(int8 x = 0; x < 24; x++){
//         a = ((int192*)*p & 63);
//         in.x = (a & );
//         out = s_box(w[x]);
//         w[x] = w_;
//     }

//     output = (int192)*p;

//     return output;
// }

void show_int_192(int8 *ident, int192 input)
{
    void *mem;
    int32 *p;
    int8 i;

    printf("%s = 0x", ident);
    mem = $v($v & input-4);
    for (i = 0; i < 6; i++)
    {
        mem += 4;
        p = (int32 *)mem;
        printf("%x.88x", $i * p);
    }
    printf("\n");
    return;
}

void show_int_128(int8 *ident, int128 input)
{
    void *mem;
    int32 *p;
    int8 i;

    printf("%s = 0x", ident);
    mem = $v($v & input - 4);
    for (i = 0; i < 4   ; i++)
    {
        mem += 4;
        p = (int32 *)mem;
        printf("%x.08x", $i * p);
    }
    printf("\n");
    return;
}

void *showroundkey(int8 *id, roundkey *rk){
    assert(rk);
    printf("%s = {\n",$c id);
    printf(" id=%d\n",rk->id);
    printf(" rc=%lld\n ",rk->round_constant_rc);

    show(rk->subkey);
    printf("}\n");
    return;
}

int192 s_boxes(int192 input)
{
    semiwords word;
    int192 input_;
    int16 in, in_, out;
    int8 msbs;

    input_ = input;
    for (int8 i = 0; i < 16; i++)
    {
        show(intput_);
        in = (input_.x & 0x0fff);
        msbs = ((in >> 12) & 0x0f);
        word.x = (in & 0x0f);
        word.y = ((in >> 4) & 0x0f);
        word.z = ((in >> 8) & 0x0f);

        in_ = (in & 0x0fff);
        out = ((msbs << 12) | in_);

        word = s_box(word);

        input_.x <<= 16;
        input_.x |= out;
    }

    return input_;
}

semiwords s_box(semiwords input)
{
    return input;
}

int128 c_box(int192 input)
{
    int128 output;

    output = input.x;

    return output;
}

int128 f(int128 input)
{
    int128 output;

    output = c_box(s_boxes(x_box(input)));

    return output;
}

int main()
{
    roundkey *p;

    p = gen_subkey($16 0x50505050);

    do{
        show(p);
    }while(p = p->next);



    return 0;
}

roundkey *make_roundkey(int8 id, int128 subkey, int64 round_constant_rc)
{
    int16 size;
    roundkey *p;

    size = sizeof(struct s_roundkey);
    p = alloc(size);
    assert(p != NULL);

    p->id = id;
    p->subkey = subkey;
    p->round_constant_rc = round_constant_rc;
    p->next = (roundkey *)0;

    return p;
}

int128 make_subkey(int8 id, int128 subkey, int64 round_constant_rc)
{
    return subkey;
}

roundkey *gen_subkey(int128 key)
{
    roundkey *p, *first, *last;
    int128 subkey;
    int8 x;

    x = 0;
    first = make_roundkey(x++, key, rcs[x]);

    for (p = first; x < 16; x++)
    {
        p = make_roundkey(x, last->subkey, rcs[x]);
        last->next = p;
        last = p;
    }
    last->next = first;
    return first;
}