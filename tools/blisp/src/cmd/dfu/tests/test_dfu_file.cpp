//
// Created by ralim on 26/09/22.
//

#include "Config.h"
#include "dfu_file.h"
#include <gtest/gtest.h>
TEST(DFU_FILE_PARSER, ParseTestFile) {
    uint8_t* payload = nullptr;
    size_t payload_size = 0;
    int res = dfu_file_parse(SOURCE_DIR "/Pinecilv2_EN.dfu", &payload,
                             &payload_size);
    ASSERT_EQ(res, 0);
    ASSERT_EQ(payload_size, 1024);
}