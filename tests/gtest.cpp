#include <gtest/gtest.h>
#include "observer.h"
#include "packet.h"

TEST(TestBulk, test1) {
    testing::internal::CaptureStdout();
    Packet pack;
    Cmd_Observer cmdob(&pack);
    pack.set_number(3);
    pack.setstring("cmd1");
    pack.setstring("cmd2");
    pack.setstring("cmd3");
    pack.setstring("cmd4");
    pack.setstring("cmd5");
    pack.modul();
    pack.notify();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string("bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5\n"));
}

TEST(TestBulk, test2) {
    testing::internal::CaptureStdout();
    Packet pack;
    Cmd_Observer cmdob(&pack);
    pack.set_number(3);
    pack.setstring("cmd1");
    pack.setstring("cmd2");
    pack.setstring("cmd3");
    pack.setstring("{");
    pack.setstring("cmd4");
    pack.setstring("cmd5");
    pack.setstring("cmd6");
    pack.setstring("cmd7");
    pack.setstring("}");
    pack.modul();
    pack.notify();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string("bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5, cmd6, cmd7\n"));
}

TEST(TestBulk, test3) {
    testing::internal::CaptureStdout();
    Packet pack;
    Cmd_Observer cmdob(&pack);
    pack.set_number(3);
    pack.setstring("{");
    pack.setstring("cmd1");
    pack.setstring("cmd2");
    pack.setstring("{");
    pack.setstring("cmd3");
    pack.setstring("cmd4");
    pack.setstring("}");
    pack.setstring("cmd5");
    pack.setstring("cmd6");
    pack.setstring("}");
    pack.modul();
    pack.notify();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string("bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n"));
}

TEST(TestBulk, test4) {
    testing::internal::CaptureStdout();
    Packet pack;
    Cmd_Observer cmdob(&pack);
    pack.set_number(3);
    pack.setstring("cmd1");
    pack.setstring("cmd2");
    pack.setstring("cmd3");
    pack.setstring("{");
    pack.setstring("cmd4");
    pack.setstring("cmd5");
    pack.setstring("cmd6");
    pack.setstring("cmd7");
    pack.modul();
    pack.notify();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string("bulk: cmd1, cmd2, cmd3\n"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
