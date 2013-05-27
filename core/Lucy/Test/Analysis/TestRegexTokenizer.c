/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define C_TESTLUCY_TESTREGEXTOKENIZER
#define TESTLUCY_USE_SHORT_NAMES
#include "Lucy/Util/ToolSet.h"

#include "Clownfish/Test/TestFormatter.h"
#include "Lucy/Test.h"
#include "Lucy/Test/Analysis/TestRegexTokenizer.h"
#include "Lucy/Analysis/RegexTokenizer.h"


TestRegexTokenizer*
TestRegexTokenizer_new(TestFormatter *formatter) {
    TestRegexTokenizer *self
        = (TestRegexTokenizer*)VTable_Make_Obj(TESTREGEXTOKENIZER);
    return TestRegexTokenizer_init(self, formatter);
}

TestRegexTokenizer*
TestRegexTokenizer_init(TestRegexTokenizer *self, TestFormatter *formatter) {
    return (TestRegexTokenizer*)TestBatch_init((TestBatch*)self, 3, formatter);
}

static void
test_Dump_Load_and_Equals(TestBatch *batch) {
    if (!RegexTokenizer_is_available()) {
        SKIP(batch, "RegexTokenizer not available");
        SKIP(batch, "RegexTokenizer not available");
        SKIP(batch, "RegexTokenizer not available");
        return;
    }

    ZombieCharBuf *word_char_pattern  = ZCB_WRAP_STR("\\w+", 3);
    ZombieCharBuf *whitespace_pattern = ZCB_WRAP_STR("\\S+", 3);
    RegexTokenizer *word_char_tokenizer
        = RegexTokenizer_new((CharBuf*)word_char_pattern);
    RegexTokenizer *whitespace_tokenizer
        = RegexTokenizer_new((CharBuf*)whitespace_pattern);
    Obj *word_char_dump  = RegexTokenizer_Dump(word_char_tokenizer);
    Obj *whitespace_dump = RegexTokenizer_Dump(whitespace_tokenizer);
    RegexTokenizer *word_char_clone
        = RegexTokenizer_Load(whitespace_tokenizer, word_char_dump);
    RegexTokenizer *whitespace_clone
        = RegexTokenizer_Load(whitespace_tokenizer, whitespace_dump);

    TEST_FALSE(batch,
               RegexTokenizer_Equals(word_char_tokenizer, (Obj*)whitespace_tokenizer),
               "Equals() false with different pattern");
    TEST_TRUE(batch,
              RegexTokenizer_Equals(word_char_tokenizer, (Obj*)word_char_clone),
              "Dump => Load round trip");
    TEST_TRUE(batch,
              RegexTokenizer_Equals(whitespace_tokenizer, (Obj*)whitespace_clone),
              "Dump => Load round trip");

    DECREF(word_char_tokenizer);
    DECREF(word_char_dump);
    DECREF(word_char_clone);
    DECREF(whitespace_tokenizer);
    DECREF(whitespace_dump);
    DECREF(whitespace_clone);
}

void
TestRegexTokenizer_run_tests(TestRegexTokenizer *self) {
    TestBatch *batch = (TestBatch*)self;
    test_Dump_Load_and_Equals(batch);
}



