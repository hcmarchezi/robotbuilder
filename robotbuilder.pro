
TEMPLATE = app
TARGET = robotbuilder

CONFIG += qt opengl warn_on debug
CONFIG -= dlopen_opengl
DEPENDPATH = ../include

REQUIRES = opengl

HEADERS =  \
src/Application.h \
src/Face.h \
src/GLLink.h \
src/GLObject.h \
src/GraphicObject.h \
src/LinkApp.h \
src/Link.h \
src/LinkPosition.h \
src/LinkType.h \
src/PersistentLink.h \
src/PersistentLinkType.h \
src/PersistentObject.h \
src/PersistentPrismaticLinkType.h \
src/PersistentRevoluteLinkType.h \
src/PersistentRobot.h \
src/Point.h \
src/PrismaticLinkType.h \
src/QHSpinBox.h \
src/RevoluteLinkType.h \
src/RobotApp.h \
src/Robot.h \
src/RobotPosition.h \
src/TrajectoryApp.h \
src/Trajectory.h \
src/WLinkTypeCreation.h \
src/WLinkTypeSelection.h \
src/WLinkTypeView.h \
src/WMain.h \
src/WRobotConstruction.h \
src/WRobotCreation.h \
src/WRobotTrajectory.h \
src/WSelection.h \
src/WTrajectory.h \
src/WView.h \
  tinystr.h \
  tinyxml.h \
  src/tinystr.h \
  src/tinyxml.h \
  src/AuxTextFileReader.h \
  src/AuxTextFile.h

SOURCES = \
src/Application.cpp \
src/Face.cpp \
src/GLLink.cpp \
src/GLObject.cpp \
src/GraphicObject.cpp \
src/LinkApp.cpp \
src/Link.cpp \
src/LinkPosition.cpp \
src/LinkType.cpp \
src/maincgt.cpp \
src/PersistentLink.cpp \
src/PersistentLinkType.cpp \
src/PersistentObject.cpp \
src/PersistentPrismaticLinkType.cpp \
src/PersistentRevoluteLinkType.cpp \
src/PersistentRobot.cpp \
src/Point.cpp \
src/PrismaticLinkType.cpp \
src/QHSpinBox.cpp \
src/RevoluteLinkType.cpp \
src/RobotApp.cpp \
src/Robot.cpp \
src/RobotPosition.cpp \
src/TrajectoryApp.cpp \
src/Trajectory.cpp \
src/WLinkTypeCreation.cpp \
src/WLinkTypeSelection.cpp \
src/WLinkTypeView.cpp \
src/WMain.cpp \
src/WRobotConstruction.cpp \
src/WRobotCreation.cpp \
src/WRobotTrajectory.cpp \
src/WSelection.cpp \
src/WTrajectory.cpp \
src/WView.cpp \
 tinystr.cpp \
 tinyxml.cpp \
 tinyxmlerror.cpp \
 tinyxmlparser.cpp \
 src/tinystr.cpp \
 src/tinyxml.cpp \
 src/tinyxmlerror.cpp \
 src/tinyxmlparser.cpp \
 src/AuxTextFileReader.cpp \
 src/AuxTextFile.cpp


SOURCES -= AuxTextFileReader.cpp \
tinystr.cpp \
tinyxml.cpp \
tinyxmlerror.cpp \
tinyxmlparser.cpp \
src/AuxTextFileReader.cpp \
src/tinystr.cpp \
src/tinyxml.cpp \
src/tinyxmlerror.cpp \
src/tinyxmlparser.cpp
HEADERS -= AuxTextFileReader.h \
tinystr.h \
tinyxml.h \
src/AuxTextFileReader.h \
src/tinystr.h \
src/tinyxml.h
