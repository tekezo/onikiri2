
#ifndef ONIKIRI2_COMPLIANCE_TEST_H
#define ONIKIRI2_COMPLIANCE_TEST_H

#define RV_COMPLIANCE_RV32M


// gp レジスタに，その時実行中のテスト番号が格納される
#define TESTNUM gp


// pass: fail: の直後にこのマクロが展開される
#define RV_COMPLIANCE_HALT \
    li TESTNUM, 1;                      \
    SWSIG (0, TESTNUM);                 \
    j onikiri2_test_main_end ;


// エントリポイント
// main.c から関数として呼ばれる
// 全レジスタを保存する
#define RV_COMPLIANCE_CODE_BEGIN \
    .text ;\
    .align 4 ;\
    .global onikiri2_test_main ;\
    onikiri2_test_main: ;\
        ONIKIRI2_SAVE_REGS() ;\

// 終了
// スタックポインタを含むレジスタが破壊されているので，復元し，
// 検証用のシグニチャをダンプした後，main.c に返る
#define RV_COMPLIANCE_CODE_END \
    onikiri2_test_main_end: ; \
        ONIKIRI2_RESTORE_REGS() ;\
        ONIKIRI2_SAVE_REGS() ;\
        la a0, _onikiri2_begin_output_data ;\
        la a1, _onikiri2_end_output_data ;  \
        jal onikiri2_rvtest_print_result ;  \
        ONIKIRI2_RESTORE_REGS() ;\
        ret ;


// "_onikiri2_begin_output_data" must be aligned
#define RV_COMPLIANCE_DATA_BEGIN \
    .align 4 ;\
    _onikiri2_begin_output_data:

// "_onikiri2_end_output_data" also must be aligned
#define RV_COMPLIANCE_DATA_END \
    .align 4; \
    _onikiri2_end_output_data:

// レジスタ保存
#define ONIKIRI2_SAVE_REGS() \
    addi sp, sp, -4*32 ;\
    sw x0, 0*4(sp) ;\
    sw x1, 1*4(sp) ;\
    sw x2, 2*4(sp) ;\
    sw x3, 3*4(sp) ;\
    sw x4, 4*4(sp) ;\
    sw x5, 5*4(sp) ;\
    sw x6, 6*4(sp) ;\
    sw x7, 7*4(sp) ;\
    sw x8, 8*4(sp) ;\
    sw x9, 9*4(sp) ;\
    sw x10, 10*4(sp) ;\
    sw x11, 11*4(sp) ;\
    sw x12, 12*4(sp) ;\
    sw x13, 13*4(sp) ;\
    sw x14, 14*4(sp) ;\
    sw x15, 15*4(sp) ;\
    sw x16, 16*4(sp) ;\
    sw x17, 17*4(sp) ;\
    sw x18, 18*4(sp) ;\
    sw x19, 19*4(sp) ;\
    sw x20, 20*4(sp) ;\
    sw x21, 21*4(sp) ;\
    sw x22, 22*4(sp) ;\
    sw x23, 23*4(sp) ;\
    sw x24, 24*4(sp) ;\
    sw x25, 25*4(sp) ;\
    sw x26, 26*4(sp) ;\
    sw x27, 27*4(sp) ;\
    sw x28, 28*4(sp) ;\
    sw x29, 29*4(sp) ;\
    sw x30, 30*4(sp) ;\
    sw x31, 31*4(sp) ;\
    la t0, onikiri2_sp_save ;\
    sw sp, 0(t0) ;\

// レジスタ復帰
#define ONIKIRI2_RESTORE_REGS() \
    la t0, onikiri2_sp_save ;\
    lw sp, 0(t0) ;\
    lw x0, 0*4(sp) ;\
    lw x1, 1*4(sp) ;\
    lw x2, 2*4(sp) ;\
    lw x3, 3*4(sp) ;\
    lw x4, 4*4(sp) ;\
    lw x5, 5*4(sp) ;\
    lw x6, 6*4(sp) ;\
    lw x7, 7*4(sp) ;\
    lw x8, 8*4(sp) ;\
    lw x9, 9*4(sp) ;\
    lw x10, 10*4(sp) ;\
    lw x11, 11*4(sp) ;\
    lw x12, 12*4(sp) ;\
    lw x13, 13*4(sp) ;\
    lw x14, 14*4(sp) ;\
    lw x15, 15*4(sp) ;\
    lw x16, 16*4(sp) ;\
    lw x17, 17*4(sp) ;\
    lw x18, 18*4(sp) ;\
    lw x19, 19*4(sp) ;\
    lw x20, 20*4(sp) ;\
    lw x21, 21*4(sp) ;\
    lw x22, 22*4(sp) ;\
    lw x23, 23*4(sp) ;\
    lw x24, 24*4(sp) ;\
    lw x25, 25*4(sp) ;\
    lw x26, 26*4(sp) ;\
    lw x27, 27*4(sp) ;\
    lw x28, 28*4(sp) ;\
    lw x29, 29*4(sp) ;\
    lw x30, 30*4(sp) ;\
    lw x31, 31*4(sp) ;\
    addi sp, sp, 4*32 \




// main.c で定義
// begin から end の範囲をダンプ
// void onikiri2_rvtest_print_result(uint32_t* begin, uint32_t*end)
.extern onikiri2_rvtest_print_result

//
// data/code sections
//

.data
.align 8
// スタックポインタの保存用領域
onikiri2_sp_save:
    .dword 0x0000000000000000


#endif  // RSD_COMPLIANCE_TEST_H
