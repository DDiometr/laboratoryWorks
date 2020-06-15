#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H
#include<IKeypad.h>
#include<ILatch.h>
#include<lockcontroller.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<string>

using namespace testing;

class MockIKeypad : public IKeypad{
public:
    MOCK_METHOD(void, wait,(),(override));
    MOCK_METHOD(bool,isActive,(),(override));
    MOCK_METHOD(PasswordResponse, requestPassword,(),(override));
};

class MockILatch : public ILatch{
public:
    MOCK_METHOD(bool, isActive, (),(override));
    MOCK_METHOD(DoorStatus, open, (),(override));
    MOCK_METHOD(DoorStatus, close, (),(override));
    MOCK_METHOD(DoorStatus, getDoorStatus, (),(override));
};


TEST(Device, Test1){
    //Arrange
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(keypad1, wait()).Times(1).WillOnce(Return());
    //Act
    controller1.wait();
    //Assert

}

TEST(Device, Test2){
    bool test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, getDoorStatus()).Times(1).WillOnce(Return(DoorStatus::CLOSE));
    //Act
    test = controller1.isDoorOpen();
    //Assert
    ASSERT_EQ(test, false);
}

TEST(Device, Test3){
    bool test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, getDoorStatus()).Times(1).WillOnce(Return(DoorStatus::OPEN));
    //Act
    test = controller1.isDoorOpen();
    //Assert
    ASSERT_EQ(test, true);
}

TEST(Device, Test4){
    //Arrange
    DoorStatus test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, open()).Times(1).WillOnce(Return(DoorStatus::OPEN));
    //Act
    test = controller1.unlockDoor();
    //Assert
    ASSERT_EQ(test, DoorStatus::OPEN);
}

TEST(Device, Test5){
    //Arrange
    DoorStatus test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, close()).Times(1).WillOnce(Return(DoorStatus::CLOSE));
    //Act
    test = controller1.lockDoor();
    //Assert
    ASSERT_EQ(test, DoorStatus::CLOSE);
}

TEST(Device, Test6){
    //Arrange
    HardWareStatus test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, isActive()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(keypad1, isActive()).Times(1).WillOnce(Return(true));
    //Act
    test = controller1.hardWareCheck();
    //Assert
    ASSERT_EQ(test, HardWareStatus::OK);
}

TEST(Device, Test7){
    //Arrange
    HardWareStatus test;
    MockILatch latch1 {};
    LockController controller1 {nullptr,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, isActive()).Times(AtLeast(0)).WillOnce(Return(true));
    //Act
    test = controller1.hardWareCheck();
    //Assert
    ASSERT_EQ(test, HardWareStatus::ERROR);
}

TEST(Device, Test8){
    //Arrange
    HardWareStatus test;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(latch1, isActive()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(keypad1, isActive()).Times(1).WillOnce(Return(true));
    //Act
    test = controller1.hardWareCheck();
    //Assert
    ASSERT_EQ(test, HardWareStatus::ERROR);
}

TEST(Device, Test9){
    //Arrange
    bool test;
    PasswordResponse data;
    data.password = "0000";

    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(keypad1, requestPassword()).Times(1).WillOnce(Return(data));
    //Act
    test = controller1.isCorrectPassword();
    //Assert
    EXPECT_EQ(test, true);
}

TEST(Device, Test10){
    //Arrange
    bool test;
    PasswordResponse data;
    data.password = "1111";

    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(keypad1, requestPassword()).Times(1).WillOnce(Return(data));
    //Act
    test = controller1.isCorrectPassword();
    //Assert
    EXPECT_EQ(test, false);
}

TEST(Device, Test11){
    //Arrange

    PasswordResponse data;
    data.password = "0000";
    data.status = PasswordResponse::Status::OK;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(keypad1, requestPassword()).Times(AtLeast(1)).WillOnce(Return(data));
    controller1.resetPassword();
    //Assert
    ASSERT_EQ(controller1.isCorrectPassword(), true);
}

TEST(Device, Test12){
    //Arrange

    PasswordResponse data;
    data.password = "0000";
    data.status = PasswordResponse::Status::OK;
    PasswordResponse data2;
    data2.password = "9876";
    data2.status = PasswordResponse::Status::OK;
    PasswordResponse data3;
    data3.password = "9876";
    data3.status = PasswordResponse::Status::OK;
    PasswordResponse data4;
    data4.password = "5555";
    data4.status = PasswordResponse::Status::OK;
    PasswordResponse data5;
    data5.password = "5555";
    data5.status = PasswordResponse::Status::OK;
    MockIKeypad keypad1 {};
    MockILatch latch1 {};
    LockController controller1 {&keypad1,&latch1};
    //Prepare mocks
    EXPECT_CALL(keypad1, requestPassword()).Times(5).WillOnce(Return(data)).WillOnce(Return(data2)).WillOnce(Return(data3)).WillOnce(Return(data4)).WillOnce(Return(data5));
    controller1.resetPassword();

    //Act
    controller1.resetPassword();
    //Assert
    ASSERT_EQ(controller1.isCorrectPassword(), true);
}
#endif // TST_TESTDIVISIONBYZERO_H



