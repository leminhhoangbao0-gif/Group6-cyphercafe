<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>RegisterWindow</class>
 <widget class="QWidget" name="RegisterWindow">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>380</width>
    <height>460</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>Cyber Cafe - Register</string>
  </property>
  <layout class="QVBoxLayout" name="verticalLayout">
   <item>
    <widget class="QLabel" name="titleLabel">
     <property name="text">
      <string>Create an Account</string>
     </property>
     <property name="alignment">
      <set>Qt::AlignHCenter</set>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="usernameLabel">
     <property name="text">
      <string>Username</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="usernameLineEdit">
     <property name="placeholderText">
      <string>Choose a username</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="fullNameLabel">
     <property name="text">
      <string>Full Name</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="fullNameLineEdit">
     <property name="placeholderText">
      <string>Your full name</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="emailLabel">
     <property name="text">
      <string>Email</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="emailLineEdit">
     <property name="placeholderText">
      <string>your.email@example.com</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="phoneLabel">
     <property name="text">
      <string>Phone</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="phoneLineEdit">
     <property name="placeholderText">
      <string>Phone number</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="passwordLabel">
     <property name="text">
      <string>Password</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="passwordLineEdit">
     <property name="echoMode">
      <enum>QLineEdit::Password</enum>
     </property>
     <property name="placeholderText">
      <string>At least 6 characters</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="confirmPasswordLabel">
     <property name="text">
      <string>Confirm Password</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLineEdit" name="confirmPasswordLineEdit">
     <property name="echoMode">
      <enum>QLineEdit::Password</enum>
     </property>
     <property name="placeholderText">
      <string>Re-enter password</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QLabel" name="errorLabel">
     <property name="text">
      <string></string>
     </property>
     <property name="styleSheet">
      <string notr="true">color: red;</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QPushButton" name="registerButton">
     <property name="text">
      <string>Register</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QPushButton" name="goToLoginButton">
     <property name="text">
      <string>Already have an account? Log in</string>
     </property>
     <property name="flat">
      <bool>true</bool>
     </property>
    </widget>
   </item>
  </layout>
 </widget>
 <resources/>
 <connections/>
</ui>
