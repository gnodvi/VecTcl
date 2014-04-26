#ifndef VECTCLINT_H
#define VECTCLINT_H
#include <tcl.h>
#include "vectcl.h"

#ifdef DEBUG_REFCOUNT
#include <stdio.h>
#define DEBUGPRINTF(X) printf X
#else
#define DEBUGPRINTF(X)
#endif

/* Token pasting macro */
#define NUMARRAYTPASTER(X, Y) X##Y
#define NUMARRAYTPASTER3(X, Y, Z) X##Y##Z
#define NUMARRAYTPASTER4(X, Y, Z, W) X##Y##Z##W

extern const char * NumArray_typename[NumArray_SentinelType];

/* Macros for preprocessor magic
 * Convert between C type and numeric array type */

#define C_FROM_NATYPE_NumArray_Int64 int
#define C_FROM_NATYPE_NumArray_Float64 double
#define C_FROM_NATYPE_NumArray_Complex128 NumArray_Complex

#define NATYPE_FROM_C_int	NumArray_Int64
#define NATYPE_FROM_C_double NumArray_Float64
#define NATYPE_FROM_C_NumArray_Complex NumArray_Complex128

#define C_FROM_NATYPE(X) NUMARRAYTPASTER(C_FROM_NATYPE_, X)
#define NATYPE_FROM_C(X) NUMARRAYTPASTER(NATYPE_FROM_C_, X)

/* Macro to handle upcasting */
#define UPCAST(TFROM, TTO, X) NUMARRAYTPASTER4(UPCAST_, TFROM, _, TTO)(X)

#define UPCAST_int_int(X) X
#define UPCAST_int_double(X) X
#define UPCAST_double_double(X) X
#define UPCAST_int_NumArray_Complex(X) NumArray_mkComplex(X, 0.0)
#define UPCAST_double_NumArray_Complex(X) NumArray_mkComplex(X, 0.0)
#define UPCAST_NumArray_Complex_NumArray_Complex(X) X

#define UPCAST_COMMON(T1, T2) NUMARRAYTPASTER4(UPCAST_COMMON_, T1, _, T2)
#define UPCAST_COMMON_int_int int
#define UPCAST_COMMON_int_double double
#define UPCAST_COMMON_double_int double
#define UPCAST_COMMON_double_double double
#define UPCAST_COMMON_int_NumArray_Complex NumArray_Complex
#define UPCAST_COMMON_NumArray_Complex_int NumArray_Complex
#define UPCAST_COMMON_double_NumArray_Complex NumArray_Complex
#define UPCAST_COMMON_NumArray_Complex_double NumArray_Complex
#define UPCAST_COMMON_NumArray_Complex_NumArray_Complex NumArray_Complex

/* Useful to print formatted error messages */
#define RESULTPRINTF(X) Tcl_SetObjResult(interp, Tcl_ObjPrintf X)

extern const Tcl_ObjType NumArrayTclType;

void NumArrayIncrRefcount(Tcl_Obj* naObj);
void NumArrayDecrRefcount(Tcl_Obj* naObj);

void NumArrayStripSingletonDimensions(NumArrayInfo *info);
void NumArrayUnshareBuffer(Tcl_Obj *naObj);
int NumArrayIsShared(NumArraySharedBuffer *sharedbuf);

int NumArrayCompatibleDimensions(NumArrayInfo *info1, NumArrayInfo *info2);

#define SUBCOMMAND(X) \
	int	X(ClientData dummy, Tcl_Interp *interp,\
		int objc, Tcl_Obj *const *objv)

SUBCOMMAND(NumArrayCreateCmd);
SUBCOMMAND(NumArrayConstFillCmd);
SUBCOMMAND(NumArrayEyeCmd);
SUBCOMMAND(NumArrayInfoCmd);
SUBCOMMAND(NumArrayDimensionsCmd);
SUBCOMMAND(NumArrayShapeCmd);
SUBCOMMAND(NumArrayReshapeCmd);
SUBCOMMAND(NumArrayTransposeCmd);
SUBCOMMAND(NumArrayAdjointCmd);
SUBCOMMAND(NumArraySliceCmd);
SUBCOMMAND(NumArraySetCmd);
SUBCOMMAND(NumArrayGetCmd);
SUBCOMMAND(NumArrayFastCopyCmd);
SUBCOMMAND(NumArrayFastAddCmd);
SUBCOMMAND(NumArrayLinRegCmd);
SUBCOMMAND(NumArrayConvDoubleCmd);
SUBCOMMAND(NumArrayConvComplexCmd);
SUBCOMMAND(NumArrayAbsCmd);
SUBCOMMAND(NumArraySignCmd);
SUBCOMMAND(NumArrayRealCmd);
SUBCOMMAND(NumArrayImagCmd);
SUBCOMMAND(NumArrayArgCmd);
SUBCOMMAND(NumArrayConjCmd);
SUBCOMMAND(NumArrayPlusCmd);
SUBCOMMAND(NumArrayMinusCmd);
SUBCOMMAND(NumArrayTimesCmd);
SUBCOMMAND(NumArrayLdivideCmd);
SUBCOMMAND(NumArrayRdivideCmd);
/* relation operators */
SUBCOMMAND(NumArrayGreaterCmd);
SUBCOMMAND(NumArrayLesserCmd);
SUBCOMMAND(NumArrayGreaterEqualCmd);
SUBCOMMAND(NumArrayLesserEqualCmd);
SUBCOMMAND(NumArrayEqualCmd);
SUBCOMMAND(NumArrayUnequalCmd);
/* boolean operators */
SUBCOMMAND(NumArrayNotCmd);
SUBCOMMAND(NumArrayAndCmd);
SUBCOMMAND(NumArrayOrCmd);

SUBCOMMAND(NumArrayBackslashCmd);
SUBCOMMAND(NumArraySlashCmd);
SUBCOMMAND(NumArrayMatrixPowCmd);
SUBCOMMAND(NumArrayReminderCmd);
SUBCOMMAND(NumArrayPowCmd);
SUBCOMMAND(NumArrayMinCmd);
SUBCOMMAND(NumArrayMaxCmd);
SUBCOMMAND(NumArraySetAssignCmd);
SUBCOMMAND(NumArrayPlusAssignCmd);
SUBCOMMAND(NumArrayMinusAssignCmd);
SUBCOMMAND(NumArrayTimesAssignCmd);
SUBCOMMAND(NumArrayLdivideAssignCmd);
SUBCOMMAND(NumArrayRdivideAssignCmd);
SUBCOMMAND(NumArrayPowAssignCmd);
SUBCOMMAND(NumArrayNegCmd);
SUBCOMMAND(NumArrayNegCmd);
SUBCOMMAND(NumArraySinCmd);
SUBCOMMAND(NumArrayCosCmd);
SUBCOMMAND(NumArrayTanCmd);
SUBCOMMAND(NumArrayExpCmd);
SUBCOMMAND(NumArrayLogCmd);
SUBCOMMAND(NumArraySqrtCmd);
SUBCOMMAND(NumArraySinhCmd);
SUBCOMMAND(NumArrayCoshCmd);
SUBCOMMAND(NumArrayTanhCmd);
SUBCOMMAND(NumArrayAsinCmd);
SUBCOMMAND(NumArrayAcosCmd);
SUBCOMMAND(NumArrayAtanCmd);
SUBCOMMAND(NumArrayAsinhCmd);
SUBCOMMAND(NumArrayAcoshCmd);
SUBCOMMAND(NumArrayAtanhCmd);
SUBCOMMAND(NumArrayQRecoCmd);
SUBCOMMAND(NumArraySumCmd);
SUBCOMMAND(NumArrayAxisMinCmd);
SUBCOMMAND(NumArrayAxisMaxCmd);
SUBCOMMAND(NumArrayMeanCmd);
SUBCOMMAND(NumArrayStdCmd);
SUBCOMMAND(NumArrayStd1Cmd);
SUBCOMMAND(NumArrayAllCmd);
SUBCOMMAND(NumArrayAnyCmd);

#endif
