#ifndef FKO_INST_H
#define FKO_INST_H

enum comp_flag
/*
 * enumerated type for compiler flag, so format is:
 * CMPFLAG, <enum comp_flag>, <info1>, <info2>
 */
{
   CF_REGSAVE,
   CF_REGRESTORE,
   CF_PARASAVE,
   CF_LOOP_INIT,  /* loop# */
   CF_LOOP_BODY,
   CF_LOOP_UPDATE,
   CF_LOOP_TEST,
   CF_LOOP_END,
   CF_VRED_END
};

/*
 *
 * [r]  = integer register
 * [fr] = fp register
 * [c]  = constant
 * [cc] = condition code
 *
 * Unless otherwise noted, all instructions have format:
 * [r0], [r1], [r2/c2]
 * NOTE: only use 1st 14 bits, 2 most sig used to encode exceptions for
 *       instructions that update more than dest:
 *       00 : normal (dest updated only)
 *       01 : dest & src1 updated
 *       10 : dest & src2 updated
 *       11 : all ops updated
 */
enum inst
{
   UNIMP,                       /* NULL, NULL, NULL */
   NOP,                         /* NULL, NULL, NULL */
   COMMENT,                     /* <string>,NULL,NULL */
   LABEL,                       /* <labname>,NULL,NULL */
   CMPFLAG,                     /* flag,flag,flag compiler info */
/*
 * integer ops of same size as ptrs
 */
   LD,                          /* [r], [ptr], NULL */
   ST,                          /* [ptr], [r], NULL */
   MOV,                         /* [r0], [r1/c] : r0 = r1 */
   OR,                          /* r0 = r1 | r/c */
   AND,                         /* r0 = r1 & r/c */
   ANDCC,                       /* r0 = r1 & r/c */
   XOR,                         /* r0 = r1 ^ r/c */
   NOT,                         /* r0 = ~r0 */
   SHL,                         /* r0 = r1 << r/c */
   SHLCC,                       /* r0 = r1 << r/c */
   SHR,                         /* r0 = r1 >> r/c, set [cc] */
   SAR,                         /* r0 = r1 >> r/c */
   ADD,                         /* r0 = r1 + r/c */
   SUB,                         /* r0 = r1 - r/c */
   SUBCC,                       /* r0 = r1 - r/c */
   MUL,                         /* r0 = r1 * r/c */
   UMUL,                        /* r0 = r1 * r/c, unsigned */
   DIV,                         /* r0 = r1 / r/c */
   UDIV,                      
   CMPAND,                      /* cc0, r1, r2/c : set [cc] based on r1 & r2 */
   CMP,                         /* cc#, r1, r2/c: set [cc] based on r1 - r2 */
   NEG,                         /* [r0], [r1] : r0 = -r1 */
/*   ABS, ; abs commented out because not widely supported */
/*
 * 32-bit integer (64-bit systems only)
 */
   LDS,                         /* [r], [ptr], NULL */
   STS,                         /* [ptr], [r], NULL */
   ORS,                         /* r0 = r1 | r/c */
   XORS,                        /* r0 = r1 ^ r/c */
   NOTS,                        /* r0 = ~r0 */
   SHLS, SHLCCS,                /* r0 = r1 << r/c */
   SHRS, SHRCCS,                /* r0 = r1 >> r/c, set [cc] */
   SARS,                        /* r0 = r1 >> r/c */
   ADDS, ADDCCS,                /* r0 = r1 + r/c */
   SUBS, SUBCCS,                /* r0 = r1 - r/c */
   MULS,                        /* r0 = r1 * r/c */
   UMULS,                       /* r0 = r1 * r/c, unsigned */
   DIVS,                        /* r0 = r1 / r/c */
   UDIVS,
   CMPS,                        /* set [cc](r0) based on r1 - r2 */
   MOVS,                        /* [r0], [r1] : r0 = r1 */
   NEGS,                        /* [r0], [r1] : r0 = -r1 */
   ABSS,
/*
 * Jump instructions
 */
   JMP,                         /* PCREG, LABEL, 0 */
   JEQ, JNE, JLT, JLE, JGT, JGE,  /* PCREG, cc#, LABEL */
   RET,                         /* NULL,NULL,NULL : return to caller */
   PREFR,                       /* NULL, [ptr] [ilvl] */
   PREFW,                       /* NULL, [ptr] [ilvl] */
/*
 * The stream prefetch instructions have format:
 * [ptr], [len], [ilvl:ist]
 * where [ilvl:ist] is an 8-bit constant, where 4 most sig bits give cache
 * level to fetch to (if leading bit is set, fetch is inclusive, else 
 * exclusive).  The last 4 bits indicate which stream to fetch with.
 * Therefore, up to 7 cache levels and 15 streams allowed.
 */
   PREFRS,                      /* [ptr], [len], [ilvl:ist] */
   PREFWS,                      /* [ptr], [len], [ilvl:ist] */
/*
 * Floating point instructions, single precision
 */
   FZERO,                       /* [fr] : fr = 0.0 */
   FLD,                         /* [fr] [ptr] */
   FST,                         /* [ptr], [fr] */
   FMAC,                        /* fr0 += fr1 * fr2 */
   FMUL,                        /* fr0 = fr1 * fr2 */
   FDIV,                        /* fr0 = fr1 / fr2 */
   FADD,                        /* fr0 = fr1 + fr2 */
   FSUB,                        /* fr0 = fr1 - fr2 */
   FABS,                        /* [fr0], [fr1] : fr0 = abs(fr1) */
   FCMP,                        /* [fr0], [fr1] : set [cc] by (fr0 - fr1) */
   FNEG,                        /* [fr0], [fr1] : fr0 = -fr1 */
   FMOV,                        /* fr0 = fr1 */
/*
 * Floating point instructions, double precision
 */
   FZEROD,                      /* [fr] : fr = 0.0 */
   FLDD,                        /* [fr] [ptr] */
   FSTD,                        /* [ptr], [fr] */
   FMACD,                       /* fr0 += fr1 * fr2 */
   FMULD,                       /* fr0 = fr1 * fr2 */
   FDIVD,                       /* fr0 = fr1 / fr2 */
   FADDD,                       /* fr0 = fr1 + fr2 */
   FSUBD,                       /* fr0 = fr1 - fr2 */
   FABSD,                       /* [fr0], [fr1] : fr0 = abs(fr1) */
   FCMPD,                       /* [fr0], [fr1] : set [cc] by (fr0 - fr1) */
   FNEGD,                       /* [fr0], [fr1] : fr0 = -fr1 */
   FMOVD,                       /* fr0 = fr1 */
/*
 * Double precision vector instructions
 * [memA] is a vector-aligned mem @ [mem] is any alignment
 */
   VDZERO,                     /* [vr0]        : vr0[0:N] = 0.0 */
   VDLD,                       /* [vr0], [memA]  : vr0 = mem */
   VDLDS,                      /* [vr0], [mem]  :  vr0[0] = mem; vr0[1] = 0 */
   VDLDL,                      /* [vr], [mem]   : vr[0] = mem; vr[1] = vr[1] */
   VDLDH,                      /* [vr], [mem]   : vr[0] = vr[0]; vr[1] = mem */
   VDST,                       /* [memA], vr0    : mem = vr0 */
   VDSTS,                      /* [mem], [vr0]  :  mem = vr[0] */
   VDMOV,                      /* [vr0], [vr1]   : vr0 = vr1 */
   VDMOVS,                     /* [vr0], [vr1]   : vr0[0] = vr1[0] */
   VDADD,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 + vr2 */
   VDSUB,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 - vr2 */
   VDMUL,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 * vr2 */
   VDABS,                      /* [vr0], [vr1] : vr0 = abs(vr1) */
   VDSHUF,                     /* [vr0], [vr1], [int32]; vr0 = shuf(vr1|vr0) */
          /* [int32] is split into 8 4 bit words; 1st word indicates which */
          /* should reside in vr0[0], 4th in vr0[3];  Words are numbered */
          /* starting in vr0[0], and ending in vr1[N], N=veclen-1 */
/*
 * Single precision vector instructions
 * [memA] is a vector-aligned mem @ [mem] is any alignment
 */
   VFZERO,                     /* [vr0]        : vr0[0:N] = 0.0 */
   VFLD,                       /* [vr0], [memA]  : vr0 = mem */
   VFLDS,                      /* [vr0], [mem]  :  vr0[0] = mem; vr0[1] = 0 */
   VFLDL,                      /* [vr], [mem]   : vr[0] = mem; vr[1] = vr[1] */
   VFLDH,                      /* [vr], [mem]   : vr[0] = vr[0]; vr[1] = mem */
   VFST,                       /* [memA], vr0    : mem = vr0 */
   VFSTS,                      /* [mem], [vr0]  :  mem = vr[0] */
   VFMOV,                      /* [vr0], [vr1]   : vr0 = vr1 */
   VFMOVS,                     /* [vr0], [vr1]   : vr0[0] = vr1[0] */
   VFADD,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 + vr2 */
   VFSUB,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 - vr2 */
   VFMUL,                      /* [vr0], [vr1], [vr2] : vr0 = vr1 * vr2 */
   VFABS,                      /* [vr0], [vr1] : vr0 = abs(vr1) */
   VFSHUF,                     /* [vr0], [vr1], [int32]; vr0 = shuf(vr1|vr0) */
          /* [int32] is split into 8 4 bit words; 1st word indicates which */
          /* should reside in vr0[0], 4th in vr0[3];  Words are numbered */
          /* starting in vr0[0], and ending in vr1[N], N=veclen-1 */
/*
 * x86-only instructions
 */
   VGR2VR16,                    /* vreg, ireg, const -- PINSRW */
   FCMPW,    /* freg0, freg1, iconst ; freg0 overwritten with T or F */
   FCMPWD,   /* iconst -- 0 : ==;  1 : < ;  2 : <= */
   CVTBFI,   /* ireg, freg    x86 only movmskps -> bit move (no conversion) */
   CVTBDI,   /* ireg, dreg    x86 only movmskpd */
/*
 * Type conversion instructions
 */
   CVTIS,
   CVTSI,
   CVTFI,
   CVTIF,
   CVTDI,
   CVTID,
   CVTFS,
   CVTSF,
   CVTDS,
   CVTSD,
   LAST_INST
};

#ifdef IFKO_DECLARE
char *instmnem[] =
{
   "UNIMP",
   "NOP",
   "COMMENT",
   "LABEL",
   "CMPFLAG",
/*
 * integer ops of same size as ptrs
 */
   "LD",
   "ST",
   "MOV",
   "OR",       /* [OR-NEG] set CC for x86 */
   "AND",
   "ANDCC",
   "XOR",
   "NOT",
   "SHL",
   "SHLCC",
   "SHR",
   "SAR",
   "ADD",
   "SUB",
   "SUBCC",
   "MUL",
   "UMUL",
   "DIV",
   "UDIV",
   "CMPAND",
   "CMP",
   "NEG",
/*   ABS, ; abs commented out because not widely supported */
/*
 * 32-bit integer (64-bit systems only)
 */
   "LDS",
   "STS",
   "MOVS",
   "ORS",
   "XORS",
   "NOTS",
   "SHLS", "SHLCCS",
   "SHRS", "SHRCCS",
   "SARS",
   "ADDS", "ADDCCS",
   "SUBS", "SUBCCS",
   "MULS",
   "UMULS",
   "DIVS",
   "UDIVS",
   "CMPS",
   "NEGS",
   "ABSS",
/*
 * Jump instructions
 */
   "JMP",
   "JEQ", "JNE", "JLT", "JLE", "JGT", "JGE",
   "RET",
   "PREFR",
   "PREFW",
/*
 * The stream prefetch instructions have format:
 * [ptr], [len], [ilvl:ist]
 * where [ilvl:ist] is an 8-bit constant, where 4 most sig bits give cache
 * level to fetch to (if leading bit is set, fetch is inclusive, else 
 * exclusive).  The last 4 bits indicate which stream to fetch with.
 * Therefore, up to 7 cache levels and 15 streams allowed.
 */
   "PREFRS",
   "PREFWS",
/*
 * Floating point instructions, single precision
 */
   "FZERO",
   "FLD",
   "FST",
   "FMAC",
   "FMUL",
   "FDIV",
   "FADD",
   "FSUB",
   "FABS",
   "FCMP",
   "FNEG",
   "FMOV",
/*
 * Floating point instructions, double precision
 */
   "FZEROD",
   "FLDD",
   "FSTD",
   "FMACD",
   "FMULD",
   "FDIVD",
   "FADDD",
   "FSUBD",
   "FABSD",
   "FCMPD",
   "FNEGD",
   "FMOVD",
/*
 * Double precision vector inst
 */
   "VDZERO",
   "VDLD",
   "VDLDS",
   "VDLDL",
   "VDLDH",
   "VDST",
   "VDSTS",
   "VDMOV",
   "VDADD",
   "VDSUB",
   "VDMUL",
   "VDABS",
   "VDSHUF",
/*
 * Single precision vector inst
 */
   "VFZERO",
   "VFLD",
   "VFLDS",
   "VFLDL",
   "VFLDH",
   "VFST",
   "VFSTS",
   "VFMOV",
   "VFADD",
   "VFSUB",
   "VFMUL",
   "VFABS",
   "VFSHUF",
/*
 * x86-only instructions
 */
   "VGR2VR16",
   "FCMPW",
   "FCMPWD",
   "CVTBFI",
   "CVTBDI",
/*
 * Type conversion instructions
 */
   "CVTIS",
   "CVTSI",
   "CVTFI",
   "CVTIF",
   "CVTDI",
   "CVTID",
   "CVTFS",
   "CVTSF",
   "CVTDS",
   "CVTSD",
   "LAST_INST"
};
#else
   extern char *instmnem[];
#endif

#define FIRSTBRANCH JMP
#define LASTBRANCH  RET

#define GET_INST(inst_) ((inst_) & 0x3FFF)
#define ACTIVE_INST(i_) ((i_) != COMMENT && (i_) != CMPFLAG)
#define IS_BRANCH(i_) ((i_) >= FIRSTBRANCH && (i_) <= LASTBRANCH)
#define IS_LOAD(i_)  ((i_) == LD || (i_) == FLD || (i_) == FLDD || \
                      (i_) == VFLD || (i_) == VDLD || (i_) == LDS || \
                      (i_) == VFLDS || (i_) == VDLDS || \
                      (i_) == VFLDL || (i_) == VFLDH || \
                      (i_) == VDLDL || (i_) == VDLDH)
#define IS_MOVE(i_) ((i_) == MOV || (i_) == FMOV || (i_) == FMOVD || \
                     (i_) == VFMOV || (i_) == VDMOV)
#define IS_STORE(i_)  ((i_) == ST || (i_) == FST || (i_) == FSTD || \
                       (i_) == VFST || (i_) == VDST || (i_) == STS || \
                       (i_) == VFSTS || (i_) == VDSTS)
#define IS_CMP(i_) ((i_) == CMP || (i_) == CMPAND || (i_) == CMPS || \
                    (i_) == FCMP || (i_) == FCMPD || (i_) == VFCMP || \
                    (i_) == VDCMP || \
                    (i_) == CFTBFI || (i_) == CFTBDI || (i_) == FCMPWD)
#define IS_IOPCC(i_) ((i_) == ANDCC || (i_) == SUBCC || (i_) == ANDCC)

INSTQ *NewInst(BBLOCK *myblk, INSTQ *prev, INSTQ *next, enum inst ins,
               short dest, short src1, short src2);
INSTQ *InsNewInst(BBLOCK *myblk, INSTQ *prev, INSTQ *next, enum inst ins,
                  short dest, short src1, short src2);
INSTQ *InsNewInstAfterLabel(BBLOCK *blk, enum inst ins,
                            short dest, short src1, short src2);
void InsInstInBlockList(BLIST *blist, int FIRST, enum inst ins,
                        short dest, short src1, short src2);
INSTQ *DelInst(INSTQ *del);
void KillAllInst(INSTQ *base);

#endif
