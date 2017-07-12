#pragma once
#define TIH_MP(...)__VA_ARGS__

#define TIH_INSTANTIATE_2(func,params,t0,t1) \
template func<t0>(params);template func<t1>(params);

#define TIH_INSTANTIATE_3(func,params,t0,t1,t2) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);

#define TIH_INSTANTIATE_4(func,params,t0,t1,t2,t3) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);

#define TIH_INSTANTIATE_5(func,params,t0,t1,t2,t3,t4) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);

#define TIH_INSTANTIATE_6(func,params,t0,t1,t2,t3,t4,t5) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);template func<t5>(params);

#define TIH_INSTANTIATE_7(func,params,t0,t1,t2,t3,t4,t5,t6) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);template func<t5>(params);\
template func<t6>(params);

#define TIH_INSTANTIATE_8(func,params,t0,t1,t2,t3,t4,t5,t6,t7) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);template func<t5>(params);\
template func<t6>(params); template func<t7>(params);

#define TIH_INSTANTIATE_9(func,params,t0,t1,t2,t3,t4,t5,t6,t7,t8) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);template func<t5>(params);\
template func<t6>(params); template func<t7>(params); template func<t8>(params);

#define TIH_INSTANTIATE_10(func,params,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9) \
template func<t0>(params);template func<t1>(params);template func<t2>(params);\
template func<t3>(params);template func<t4>(params);template func<t5>(params);\
template func<t6>(params); template func<t7>(params); template func<t8>(params);\
template func<t9>(params);

#define TIH_INSTANTIATE_DOUBLE_1_2(func,params,tall,t0,t1)\
	TIH_INSTANTIATE_2(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1))

#define TIH_INSTANTIATE_DOUBLE_1_3(func,params,tall,t0,t1,t2)\
	TIH_INSTANTIATE_3(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2))

#define TIH_INSTANTIATE_DOUBLE_1_4(func,params,tall,t0,t1,t2,t3)\
	TIH_INSTANTIATE_4(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3))

#define TIH_INSTANTIATE_DOUBLE_1_5(func,params,tall,t0,t1,t2,t3,t4)\
	TIH_INSTANTIATE_5(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4))

#define TIH_INSTANTIATE_DOUBLE_1_6(func,params,tall,t0,t1,t2,t3,t4,t5)\
	TIH_INSTANTIATE_6(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4),TIH_MP(tall,t5))

#define TIH_INSTANTIATE_DOUBLE_1_7(func,params,tall,t0,t1,t2,t3,t4,t5,t6)\
	TIH_INSTANTIATE_7(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4),TIH_MP(tall,t5),TIH_MP(tall,t6))

#define TIH_INSTANTIATE_DOUBLE_1_8(func,params,tall,t0,t1,t2,t3,t4,t5,t6,t7)\
	TIH_INSTANTIATE_8(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4),TIH_MP(tall,t5),TIH_MP(tall,t6),TIH_MP(tall,t7))

#define TIH_INSTANTIATE_DOUBLE_1_9(func,params,tall,t0,t1,t2,t3,t4,t5,t6,t7,t8)\
	TIH_INSTANTIATE_9(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4),TIH_MP(tall,t5),TIH_MP(tall,t6),TIH_MP(tall,t7),TIH_MP(tall,t8))

#define TIH_INSTANTIATE_DOUBLE_1_10(func,params,tall,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9)\
	TIH_INSTANTIATE_10(func,params,TIH_MP(tall,t0),TIH_MP(tall,t1),TIH_MP(tall,t2),\
	TIH_MP(tall,t3),TIH_MP(tall,t4),TIH_MP(tall,t5),TIH_MP(tall,t6),TIH_MP(tall,t7),TIH_MP(tall,t8),TIH_MP(tall,t9))

#define TIH_INSTANTIATE_DOUBLE_2_2(func,params,t0a,t1a,t0b,t1b)\
TIH_INSTANTIATE_DOUBLE_1_2(func,params,t0a,t0b,t1b)\
TIH_INSTANTIATE_DOUBLE_1_2(func,params,t1a,t0b,t1b)\

#define TIH_INSTANTIATE_DOUBLE_3_3(func,params,t0a,t1a,t2a,t0b,t1b,t2b)\
TIH_INSTANTIATE_DOUBLE_1_3(func,params,t0a,t0b,t1b,t2b)\
TIH_INSTANTIATE_DOUBLE_1_3(func,params,t1a,t0b,t1b,t2b)\
TIH_INSTANTIATE_DOUBLE_1_3(func,params,t2a,t0b,t1b,t2b)\

#define TIH_INSTANTIATE_DOUBLE_4_4(func,params,t0a,t1a,t2a,t3a,t0b,t1b,t2b,t3b)\
TIH_INSTANTIATE_DOUBLE_1_4(func,params,t0a,t0b,t1b,t2b,t3b)\
TIH_INSTANTIATE_DOUBLE_1_4(func,params,t1a,t0b,t1b,t2b,t3b)\
TIH_INSTANTIATE_DOUBLE_1_4(func,params,t2a,t0b,t1b,t2b,t3b)\
TIH_INSTANTIATE_DOUBLE_1_4(func,params,t3a,t0b,t1b,t2b,t3b)\

#define TIH_INSTANTIATE_DOUBLE_5_5(func,params,t0a,t1a,t2a,t3a,t4a,t0b,t1b,t2b,t3b,t4b)\
TIH_INSTANTIATE_DOUBLE_1_5(func,params,t0a,t0b,t1b,t2b,t3b,t4b)\
TIH_INSTANTIATE_DOUBLE_1_5(func,params,t1a,t0b,t1b,t2b,t3b,t4b)\
TIH_INSTANTIATE_DOUBLE_1_5(func,params,t2a,t0b,t1b,t2b,t3b,t4b)\
TIH_INSTANTIATE_DOUBLE_1_5(func,params,t3a,t0b,t1b,t2b,t3b,t4b)\
TIH_INSTANTIATE_DOUBLE_1_5(func,params,t4a,t0b,t1b,t2b,t3b,t4b)

#define TIH_INSTANTIATE_DOUBLE_6_6(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t0a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t1a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t2a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t3a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t4a,t0b,t1b,t2b,t3b,t4b,t5b)\
TIH_INSTANTIATE_DOUBLE_1_6(func,params,t5a,t0b,t1b,t2b,t3b,t4b,t5b)

#define TIH_INSTANTIATE_DOUBLE_7_7(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t6a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t0a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t1a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t2a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t3a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t4a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t5a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)\
TIH_INSTANTIATE_DOUBLE_1_7(func,params,t6a,t0b,t1b,t2b,t3b,t4b,t5b,t6b)

#define TIH_INSTANTIATE_DOUBLE_8_8(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t6a,t7a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t0a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t1a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t2a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t3a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t4a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t5a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t6a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)\
TIH_INSTANTIATE_DOUBLE_1_8(func,params,t7a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b)


#define TIH_INSTANTIATE_DOUBLE_9_9(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t6a,t7a,t8a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8b)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t0a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t1a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t2a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t3a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t4a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t5a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t6a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t7a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)\
TIH_INSTANTIATE_DOUBLE_1_9(func,params,t8a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n)

#define TIH_INSTANTIATE_DOUBLE_10_10(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t6a,t7a,t8a,t9a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8b,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t0a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t1a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t2a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t3a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t4a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t5a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t6a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t7a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t8a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\
TIH_INSTANTIATE_DOUBLE_1_10(func,params,t9a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8n,t9b)\

#define TIH_INSTATIATE_TRIPLE(func,params,t0a,t1a,t2a,t3a,t4a,t5a,t6a,t7a,t8a,t9a,t0b,t1b,t2b,t3b,t4b,t5b,t6b,t7b,t8b,t9b,t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t0a,t0b),TIH_MP(t0a,t1b),TIH_MP(t0a,t2b),TIH_MP(t0a,t3b),TIH_MP(t0a,t4b),TIH_MP(t0a,t5b),TIH_MP(t0a,t6b),TIH_MP(t0a,t7b),TIH_MP(t0a,t8b),TIH_MP(t0a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t1a,t0b),TIH_MP(t1a,t1b),TIH_MP(t1a,t2b),TIH_MP(t1a,t3b),TIH_MP(t1a,t4b),TIH_MP(t1a,t5b),TIH_MP(t1a,t6b),TIH_MP(t1a,t7b),TIH_MP(t1a,t8b),TIH_MP(t1a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t2a,t0b),TIH_MP(t2a,t1b),TIH_MP(t2a,t2b),TIH_MP(t2a,t3b),TIH_MP(t2a,t4b),TIH_MP(t2a,t5b),TIH_MP(t2a,t6b),TIH_MP(t2a,t7b),TIH_MP(t2a,t8b),TIH_MP(t2a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t3a,t0b),TIH_MP(t3a,t1b),TIH_MP(t3a,t2b),TIH_MP(t3a,t3b),TIH_MP(t3a,t4b),TIH_MP(t3a,t5b),TIH_MP(t3a,t6b),TIH_MP(t3a,t7b),TIH_MP(t3a,t8b),TIH_MP(t3a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t4a,t0b),TIH_MP(t4a,t1b),TIH_MP(t4a,t2b),TIH_MP(t4a,t3b),TIH_MP(t4a,t4b),TIH_MP(t4a,t5b),TIH_MP(t4a,t6b),TIH_MP(t4a,t7b),TIH_MP(t4a,t8b),TIH_MP(t4a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t5a,t0b),TIH_MP(t5a,t1b),TIH_MP(t5a,t2b),TIH_MP(t5a,t3b),TIH_MP(t5a,t4b),TIH_MP(t5a,t5b),TIH_MP(t5a,t6b),TIH_MP(t5a,t7b),TIH_MP(t5a,t8b),TIH_MP(t5a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t6a,t0b),TIH_MP(t6a,t1b),TIH_MP(t6a,t2b),TIH_MP(t6a,t3b),TIH_MP(t6a,t4b),TIH_MP(t6a,t5b),TIH_MP(t6a,t6b),TIH_MP(t6a,t7b),TIH_MP(t6a,t8b),TIH_MP(t6a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t7a,t0b),TIH_MP(t7a,t1b),TIH_MP(t7a,t2b),TIH_MP(t7a,t3b),TIH_MP(t7a,t4b),TIH_MP(t7a,t5b),TIH_MP(t7a,t6b),TIH_MP(t7a,t7b),TIH_MP(t7a,t8b),TIH_MP(t7a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t8a,t0b),TIH_MP(t8a,t1b),TIH_MP(t8a,t2b),TIH_MP(t8a,t3b),TIH_MP(t8a,t4b),TIH_MP(t8a,t5b),TIH_MP(t8a,t6b),TIH_MP(t8a,t7b),TIH_MP(t8a,t8b),TIH_MP(t8a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)\
TIH_INSTANTIATE_DOUBLE_10_10(func,params,TIH_MP(t9a,t0b),TIH_MP(t9a,t1b),TIH_MP(t9a,t2b),TIH_MP(t9a,t3b),TIH_MP(t9a,t4b),TIH_MP(t9a,t5b),TIH_MP(t9a,t6b),TIH_MP(t9a,t7b),TIH_MP(t9a,t8b),TIH_MP(t9a,t9b),t0c,t1c,t2c,t3c,t4c,t5c,t6c,t7c,t8c,t9c)


#undef TIH_MP







