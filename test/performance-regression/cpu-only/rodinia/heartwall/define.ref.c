//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================
//	DEFINE / INCLUDE
//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================

#include "avilib.h"

#ifndef HEARTWALL_DEFINE_C
#define HEARTWALL_DEFINE_C

#define fp float
#define ENDO_POINTS 20
#define EPI_POINTS 31
#define ALL_POINTS 51

//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================
//	PUBLIC_STRUCT
//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================

typedef struct public_struct{

	//======================================================================================================================================================
	//	WHAT USED TO BE INPUTS FROM MATLAB
	//======================================================================================================================================================

	int tSize;
	int sSize;
	int maxMove;
	fp alpha;

	int endoPoints;
	int d_endo_mem;
	int* d_endoRow;
	int* d_endoCol;
	int* d_tEndoRowLoc;
	int* d_tEndoColLoc;
	fp* d_endoT;

	int epiPoints;
	int d_epi_mem;
	int* d_epiRow;
	int* d_epiCol;
	int* d_tEpiRowLoc;
	int* d_tEpiColLoc;
	fp* d_epiT;

	int allPoints;

	//======================================================================================================================================================
	//	FRAME
	//======================================================================================================================================================

	avi_t* d_frames;
	int frames;
	int frame_no;
	fp* d_frame;
	int frame_rows;
	int frame_cols;
	int frame_elem;
	int frame_mem;

	//======================================================================================================================================================
	// 	INPUT 2
	//======================================================================================================================================================

	int in2_rows;
	int in2_cols;
	int in2_elem;
	int in2_mem;

	//======================================================================================================================================================
	//	INPUT
	//======================================================================================================================================================

	int in_mod_rows;
	int in_mod_cols;
	int in_mod_elem;
	int in_mod_mem;

	//======================================================================================================================================================
	//	CONVOLUTION
	//======================================================================================================================================================

	int ioffset;
	int joffset;

	int conv_rows;
	int conv_cols;
	int conv_elem;
	int conv_mem;

	//======================================================================================================================================================
	//	CUMULATIVE SUM 1
	//======================================================================================================================================================

	//====================================================================================================
	//	PAD ARRAY
	//====================================================================================================
	//====================================================================================================
	//	VERTICAL CUMULATIVE SUM
	//====================================================================================================

	int in2_pad_add_rows;
	int in2_pad_add_cols;

	int in2_pad_rows;
	int in2_pad_cols;
	int in2_pad_elem;
	int in2_pad_mem;

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, HORIZONTAL CUMULATIVE SUM
	//====================================================================================================
	//====================================================================================================
	//	HORIZONTAL CUMULATIVE SUM
	//====================================================================================================

	int in2_pad_cumv_sel_rowlow;
	int in2_pad_cumv_sel_rowhig;
	int in2_pad_cumv_sel_collow;
	int in2_pad_cumv_sel_colhig;

	int in2_pad_cumv_sel2_rowlow;
	int in2_pad_cumv_sel2_rowhig;
	int in2_pad_cumv_sel2_collow;
	int in2_pad_cumv_sel2_colhig;

	int in2_sub_rows;
	int in2_sub_cols;
	int in2_sub_elem;
	int in2_sub_mem;

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, SQUARE, NUMERATOR
	//====================================================================================================

	int in2_sub_cumh_sel_rowlow;
	int in2_sub_cumh_sel_rowhig;
	int in2_sub_cumh_sel_collow;
	int in2_sub_cumh_sel_colhig;

	int in2_sub_cumh_sel2_rowlow;
	int in2_sub_cumh_sel2_rowhig;
	int in2_sub_cumh_sel2_collow;
	int in2_sub_cumh_sel2_colhig;

	int in2_sub2_sqr_rows;
	int in2_sub2_sqr_cols;
	int in2_sub2_sqr_elem;
	int in2_sub2_sqr_mem;

	//======================================================================================================================================================
	//	CUMULATIVE SUM 2
	//======================================================================================================================================================

	//====================================================================================================
	//	PAD ARRAY
	//====================================================================================================
	//====================================================================================================
	//	VERTICAL CUMULATIVE SUM
	//====================================================================================================

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION
	//====================================================================================================
	//====================================================================================================
	//	HORIZONTAL CUMULATIVE SUM
	//====================================================================================================

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, DIFFERENTIAL LOCAL SUM, DENOMINATOR A, DENOMINATOR, CORRELATION
	//====================================================================================================

	//======================================================================================================================================================
	//	TEMPLATE MASK CREATE
	//======================================================================================================================================================

	int tMask_rows;
	int tMask_cols;
	int tMask_elem;
	int tMask_mem;

	//======================================================================================================================================================
	//	POINT MASK INITIALIZE
	//======================================================================================================================================================

	int mask_rows;
	int mask_cols;
	int mask_elem;
	int mask_mem;

	//======================================================================================================================================================
	//	MASK CONVOLUTION
	//======================================================================================================================================================

	int mask_conv_rows;
	int mask_conv_cols;
	int mask_conv_elem;
	int mask_conv_mem;
	int mask_conv_ioffset;
	int mask_conv_joffset;

}public_struct;

//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================
//	PRIVATE_STRUCT
//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================

typedef struct private_struct{

	//======================================================================================================================================================
	//	POINT-SPECIFIC
	//======================================================================================================================================================

	int point_no;
	int in_pointer;

	int* d_Row;
	int* d_Col;
	int* d_tRowLoc;
	int* d_tColLoc;
	fp* d_T;

	//======================================================================================================================================================
	// 	INPUT 2
	//======================================================================================================================================================

	fp* d_in2;
	fp* d_in2_sqr;

	//======================================================================================================================================================
	//	INPUT
	//======================================================================================================================================================

	fp* d_in_mod;
	fp* d_in_sqr;

	//======================================================================================================================================================
	//	CONVOLUTION
	//======================================================================================================================================================

	fp* d_conv;

	//======================================================================================================================================================
	//	CUMULATIVE SUM 1
	//======================================================================================================================================================

	//====================================================================================================
	//	PAD ARRAY
	//====================================================================================================
	//====================================================================================================
	//	VERTICAL CUMULATIVE SUM
	//====================================================================================================

	fp* d_in2_pad;

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, HORIZONTAL CUMULATIVE SUM
	//====================================================================================================
	//====================================================================================================
	//	HORIZONTAL CUMULATIVE SUM
	//====================================================================================================

	fp* d_in2_sub;

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, SQUARE, NUMERATOR
	//====================================================================================================

	fp* d_in2_sub2_sqr;

	//======================================================================================================================================================
	//	CUMULATIVE SUM 2
	//======================================================================================================================================================

	//====================================================================================================
	//	PAD ARRAY
	//====================================================================================================
	//====================================================================================================
	//	VERTICAL CUMULATIVE SUM
	//====================================================================================================

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION
	//====================================================================================================
	//====================================================================================================
	//	HORIZONTAL CUMULATIVE SUM
	//====================================================================================================

	//====================================================================================================
	//	SELECTION, SELECTION 2, SUBTRACTION, DIFFERENTIAL LOCAL SUM, DENOMINATOR A, DENOMINATOR, CORRELATION
	//====================================================================================================

	//======================================================================================================================================================
	//	TEMPLATE MASK CREATE
	//======================================================================================================================================================

	fp* d_tMask;

	//======================================================================================================================================================
	//	POINT MASK INITIALIZE
	//======================================================================================================================================================

	//======================================================================================================================================================
	//	MASK CONVOLUTION
	//======================================================================================================================================================

	fp* d_mask_conv;

	//======================================================================================================================================================
	//	SUM
	//======================================================================================================================================================

	fp* in_partial_sum;
	fp* in_sqr_partial_sum;
	fp* par_max_val;
	int* par_max_coo;

} private_struct;
#endif

//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================
//	END OF STRUCTURE
//===============================================================================================================================================================================================================
//===============================================================================================================================================================================================================
