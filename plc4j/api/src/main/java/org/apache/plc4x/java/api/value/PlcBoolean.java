/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

package org.apache.plc4x.java.api.value;

public class PlcBoolean extends PlcSimpleValue<Boolean> {

    PlcBoolean(Boolean value) {
        super(value, true);
    }

    PlcBoolean(boolean bool) {
        super(bool, false);
    }

    @Override public boolean isBoolean() {
        return true;
    }

    @Override public boolean getBoolean() {
        return value;
    }

    @Override public double getDouble() {
        return value ? 1.0 : 0.0;
    }

    @Override public float getFloat() {
        return value ? 1.0f : 0.0f;
    }

    @Override public long getLong() {
        return value ? 1 : 0;
    }

    @Override public int getInteger() {
        return value ? 1 : 0;
    }

    @Override public String getString() {
        return value ? "true" : "false";
    }

    @Override public String toString() {
        return Boolean.toString(value);
    }
}