void cpuinfo_get_info(unsigned *results) {
    asm (
        "MRC    p15, 0, R1,c0,c0\n" // ident
        "STR    R1, [R0]\n"
        "MRC    p15, 0, R1,c0,c0,1\n" // cache
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"
        "MRC    p15, 0, R1,c0,c0,2\n" // TCM
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"
        "MRC    p15, 0, R1,c1,c0\n" // control bits
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c0\n" // protection region 0
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c1\n" // protection region 1
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c2\n" // protection region 2
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c3\n" // protection region 3
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c4\n" // protection region 4
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c5\n" // protection region 5
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c6\n" // protection region 6
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c6,c7\n" // protection region 7
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c5,c0,2\n" // data accesss perm
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c5,c0,3\n" // instruction accesss perm
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c2,c0\n" // data cache config
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"
        "MRC    p15, 0, R1,c2,c0,1\n" // instruction cache config
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"
        "MRC    p15, 0, R1,c3,c0\n" // write buffer config
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c9,c1\n" // DTCM config
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        "MRC    p15, 0, R1,c9,c1,1\n" // ITCM config
        "ADD    R0, R0, #4\n"
        "STR    R1, [R0]\n"

        :::"r0","r1"
    );
}

