/**
  ******************************************************************************
  * @file    sine_model_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Jun 17 14:05:59 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "sine_model_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_sine_model_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_sine_model_weights_array_u64[161] = {
  0xbd05b6afbeb1c40eU, 0xbf0f1f0cbeba9878U, 0x3afa5db23f07ac5aU, 0x3ed8d5a43e7e921dU,
  0xbe7ded8a3f172de5U, 0x3ef398da3e9b8230U, 0xbe9a8a83be43166cU, 0xbedf686c3ec0a428U,
  0x3f16197a00000000U, 0x0U, 0xbc529110be2a7aa5U, 0x3e9db33abf1ec425U,
  0x3a2e9f06U, 0xbe02d0c0bf11f897U, 0x0U, 0x3ec7c049U,
  0x3f34141c3e31c18eU, 0xbdcda3083eb683f7U, 0x3e96eb07be31641bU, 0x3eb32193bfa4a114U,
  0x3eadf255beb6451eU, 0x3d84e715bf3b2107U, 0x3eb706233d9d9ba4U, 0xbece8c4e3ec46a08U,
  0xbecc4540be90da1cU, 0x3e39777ebd439448U, 0x3cdd1e70be9f5374U, 0x3ed043593dd150e4U,
  0xbe81367dbd26e868U, 0xbe979c90be5ed25cU, 0x3d37bdf0beb6a03fU, 0x3ea16cfdbeb0cd12U,
  0x3f0fca653df4ecd4U, 0xbcc21e10bd8b5ad4U, 0xbdb8ca4a3debaf41U, 0xbe51fa47bee37478U,
  0xbe8d19183dbca5a8U, 0x3e9039733d33e159U, 0x3d774e78bed104daU, 0x3e8bb8f3bd641613U,
  0x3f1a4d0f3ad9bd00U, 0x3e8ebd253e6ba55aU, 0x3ead3631be1d5e15U, 0xbe627ed43e348e7fU,
  0xbedd642abf2aca2cU, 0xbec30b1abe98d5ccU, 0xbebaa3bb3e904cf9U, 0x3e6f3f3ebcfde155U,
  0xbecb71b53e6226ceU, 0xbdeb45683e2becaeU, 0x3eb5b8073ed83ba3U, 0xbe4e80b43ec77751U,
  0xbe317594be782573U, 0x3e1649603e0d7565U, 0x3e75d31e3ec27d7dU, 0x3c5742e0becd3a74U,
  0xbe444d59be9c79a0U, 0xbec3ae823df65c9cU, 0xbe975660bedb8994U, 0x3eafcbf8bdb46888U,
  0x3eb8b781bea75b34U, 0x3d880108be82a85dU, 0x3c6e5de0be66ee32U, 0x3d14e5b0bb01cbc4U,
  0x3def106a3e5537daU, 0x3ded247cbc7b1460U, 0xbce86e40bd84f222U, 0xbdba54d6be2903f2U,
  0xbe09b4603ee00bbcU, 0x3eaf8f2dbf171126U, 0x3b703a003e35e3f2U, 0x3ece9ee9bdf74a62U,
  0xbd051c533e6a6392U, 0x3d56c428bec0c2feU, 0xbebb27c2bedce323U, 0x3ee4d302bf2f73d0U,
  0x3e0ebdaa3e946883U, 0x3eb6c0edbea2b544U, 0x3e8c6c6fbec44c8fU, 0xbe5374303e8f0ff2U,
  0xbecf30b63e8b5cbbU, 0xbea8a9e3beadbb2eU, 0xbcb1a66f3e465f8fU, 0x3eafdb223f1acd22U,
  0x3e5e5f86be9618d5U, 0x3e8bee493e003b45U, 0xbec2a4c63edcbae9U, 0xbe421e4c3e650782U,
  0x3e5844e0beb9695dU, 0xbe327a8ebdb1ab00U, 0x3e4e82b63d92e08cU, 0x3eb8c5e6bfa5a135U,
  0xbd15c248be32f03eU, 0xbea883c3bf67794cU, 0xbcd55630be996580U, 0xbd1b19f83ea816c7U,
  0x3f25c5eebd6454d0U, 0xbed6c7a13d6a7018U, 0xbe8e3386be75a4f5U, 0xbedaa590be9180c3U,
  0x3d590658bf1d50d6U, 0x3d8b26d7bee1606eU, 0xbd29dfe83e6b75c6U, 0xbec1dfff3e8acd8bU,
  0x3ed3404a3ed7c427U, 0x3df4fea4be5bbf47U, 0xbe0934f0beb7e3aaU, 0x3eac1026be266674U,
  0xbe8ce629bf40be68U, 0xbe00f819bed87d23U, 0x3eb05f8bbddd1afcU, 0x3e98a3eb3e10dd0bU,
  0x3f2581edbdf249d4U, 0xbe8eee703e36d8a6U, 0xbe50b95c3db2665cU, 0xbe0c1d61be70b3a4U,
  0xbe09abf63e641049U, 0xbcdbf50cbf0118bbU, 0xbdb9c9243dbe50a4U, 0x3eae4a513d033a69U,
  0xbe75098a3ec1aee7U, 0x3c3831603e161de2U, 0x3e9ae059be238cbbU, 0x3e804d393ebaa732U,
  0x3e82cd43be8a7ee4U, 0xbeb4f12a3e77e607U, 0xbeddb052be516953U, 0xbe006fee3e1e8b61U,
  0x3e8dcf813df1cb64U, 0xbe71707abe159c84U, 0x3e8fcce3be990775U, 0xbe6db19fbe0ef790U,
  0x3e93eabbbcbf6060U, 0x3cd31e803d9a6104U, 0x3e6887e6be74248aU, 0x3e572e9abeaf2ed0U,
  0xbd9ab460bb3d6200U, 0x3e98bae13e57540eU, 0xbe3a80eebe0b6a96U, 0xbeb4c2523defb2d4U,
  0x3e8aaf0dbe8ac6a2U, 0x3ed64675bea71c0fU, 0x3edba91dbe98858aU, 0xbdc06ae0becbd25bU,
  0x3ef27662U, 0x3ea860433e461b58U, 0xbd074a91bb3d2e46U, 0x3e1eecc73e744aa1U,
  0x3efd0a7dbe849166U, 0x3e99478c3e8d5bb1U, 0xbd5f1c163e2d4470U, 0x0U,
  0x3e99093e3f7e4e7dU, 0xbf487aecbe6226a9U, 0x3d2510a4be6dda9dU, 0xbf168c5bbe7b436eU,
  0x3f96d08b3f20ad0aU, 0xbf3cce06bf0c92daU, 0x3f00938dbe59a39cU, 0xbe5a1608bc2b1580U,
  0xbe8809baU,
};


ai_handle g_sine_model_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_sine_model_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

