#include <unity.h>
#include <radio_message.h>

void test_message_encode()
{
    uint8_t *msg;
    uint8_t espected[3] = {0xF1, 0xFF, 0x12};
    RadioMessage rm(0xF, 0x1, 0xFF); // create a new message by setting at build time type, progressive and key;
    msg = rm.encode(0x12);
    TEST_ASSERT_EQUAL(3, rm.getSize());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected, msg, 3);
    msg = rm.encode(0x14); // try to change value
    espected[2] = 0x14;    // shoud change only th value
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected, msg, 3);
}

void test_message_encode_change_progressives()
{
    uint8_t *msg1, *msg2;
    uint8_t espected1[3] = {0xF1, 0xFF, 0x12};
    uint8_t espected2[3] = {0xF2, 0xFF, 0x12};
    RadioMessage rm1(0xF, 0x1, 0xFF); // create a new message by setting at build time type, progressive and key;
    RadioMessage rm2(0xF, 0x2, 0xFF); // create a new message by setting the progressive to 2

    msg1 = rm1.encode(0x12);
    TEST_ASSERT_EQUAL(3, rm1.getSize());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected1, msg1, 3);

    msg2 = rm2.encode(0x12);
    TEST_ASSERT_EQUAL(3, rm2.getSize());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected2, msg2, 3);
}

void test_message_encode_change_keys()
{
    uint8_t *msg1, *msg2;
    uint8_t espected1[3] = {0xF1, 0xFA, 0x12};
    uint8_t espected2[3] = {0xF2, 0xFB, 0x12};
    RadioMessage rm1(0xF, 0x1, 0xFA); // create a new message by setting at build time type, progressive and key;
    RadioMessage rm2(0xF, 0x2, 0xFB); // create a new message by setting the progressive to 2

    msg1 = rm1.encode(0x12);
    TEST_ASSERT_EQUAL(3, rm1.getSize());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected1, msg1, 3);

    msg2 = rm2.encode(0x12);
    TEST_ASSERT_EQUAL(3, rm2.getSize());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(espected2, msg2, 3);
}

void test_message_decode_empty_msg()
{
    RadioMessage rm1;
    TEST_ASSERT_EQUAL(0x00, rm1.getType());
    TEST_ASSERT_EQUAL(0x00, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0x00, rm1.getKey());
    TEST_ASSERT_EQUAL(0x00, rm1.getValue());
}

void test_message_decode()
{
    uint8_t msg1[] = {0xF1, 0xFA, 0x12};
    RadioMessage rm1;
    rm1.decode(msg1);
    TEST_ASSERT_EQUAL(0XF, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
}

void test_message_decode_change_type()
{
    uint8_t msg1[] = {0xF1, 0xFA, 0x12};
    RadioMessage rm1;
    rm1.decode(msg1);
    TEST_ASSERT_EQUAL(0XF, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
    uint8_t msg2[] = {0xA1, 0xFA, 0x12};
    rm1.decode(msg2);
    TEST_ASSERT_EQUAL(0XA, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
}

void test_message_decode_change_progressive()
{
    uint8_t msg1[] = {0xF1, 0xFA, 0x12};
    RadioMessage rm1;
    rm1.decode(msg1);
    TEST_ASSERT_EQUAL(0XF, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
    uint8_t msg2[] = {0xA3, 0xFA, 0x12};
    rm1.decode(msg2);
    TEST_ASSERT_EQUAL(0XA, rm1.getType());
    TEST_ASSERT_EQUAL(0X3, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
}

void test_message_decode_change_key()
{
    uint8_t msg1[] = {0xF1, 0xFA, 0x12};
    RadioMessage rm1;
    rm1.decode(msg1);
    TEST_ASSERT_EQUAL(0XF, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
    uint8_t msg2[] = {0xA3, 0xFA, 0x12};
    rm1.decode(msg2);
    TEST_ASSERT_EQUAL(0XA, rm1.getType());
    TEST_ASSERT_EQUAL(0X3, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
}

void test_message_decode_change_value()
{
    uint8_t msg1[] = {0xF1, 0xFA, 0x12};
    RadioMessage rm1;
    rm1.decode(msg1);
    TEST_ASSERT_EQUAL(0XF, rm1.getType());
    TEST_ASSERT_EQUAL(0X1, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X12, rm1.getValue());
    uint8_t msg2[] = {0xA3, 0xFA, 0x15};
    rm1.decode(msg2);
    TEST_ASSERT_EQUAL(0XA, rm1.getType());
    TEST_ASSERT_EQUAL(0X3, rm1.getProgressive());
    TEST_ASSERT_EQUAL(0XFA, rm1.getKey());
    TEST_ASSERT_EQUAL(0X15, rm1.getValue());
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_message_encode);
    RUN_TEST(test_message_encode_change_progressives);
    RUN_TEST(test_message_encode_change_keys);
    RUN_TEST(test_message_decode_empty_msg);
    RUN_TEST(test_message_decode);
    RUN_TEST(test_message_decode_change_key);
    RUN_TEST(test_message_decode_change_progressive);
    RUN_TEST(test_message_decode_change_type);
    RUN_TEST(test_message_decode_change_value);
    UNITY_END();
    return 0;
}
