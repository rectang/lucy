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

package lucy

import "testing"

func TestDocMisc(t *testing.T) {
	doc := NewDoc(1)
	if got := doc.GetDocID(); got != 1 {
		t.Errorf("GetDocID: %d", got)
	}
	doc.SetDocID(42)
	if got := doc.GetDocID(); got != 42 {
		t.Errorf("Set/GetDocID: %d", got)
	}
	fields := map[string]interface{}{"title": "foo", "content": "bar"}
	doc.SetFields(fields)
	if got, ok := doc.Extract("title").(string); !ok || got != "foo" {
		t.Errorf("Extract: %v", got)
	}
}
