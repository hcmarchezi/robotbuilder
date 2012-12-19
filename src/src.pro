TEMPLATE = app
CONFIG += release \
          warn_on \
	  thread \
          qt
TARGET = ../bin/robotbuilder
SOURCES += Application.cpp \
Face.cpp \
GLLink.cpp \
GLObject.cpp \
GraphicObject.cpp \
LinkApp.cpp \
Link.cpp \
LinkPosition.cpp \
LinkType.cpp \
maincgt.cpp \
PersistentLink.cpp \
PersistentLinkType.cpp \
PersistentObject.cpp \
PersistentPrismaticLinkType.cpp \
PersistentRevoluteLinkType.cpp \
PersistentRobot.cpp \
Point.cpp \
PrismaticLinkType.cpp \
QHSpinBox.cpp \
RevoluteLinkType.cpp \
RobotApp.cpp \
Robot.cpp \
RobotPosition.cpp \
TrajectoryApp.cpp \
Trajectory.cpp \
WLinkTypeCreation.cpp \
WLinkTypeSelection.cpp \
WLinkTypeView.cpp \
WMain.cpp \
WRobotConstruction.cpp \
WRobotCreation.cpp \
WRobotTrajectory.cpp \
WSelection.cpp \
WTrajectory.cpp \
WView.cpp
HEADERS += Application.h \
Face.h \
GLLink.h \
GLObject.h \
GraphicObject.h \
LinkApp.h \
Link.h \
LinkPosition.h \
LinkType.h \
PersistentLink.h \
PersistentLinkType.h \
PersistentObject.h \
PersistentPrismaticLinkType.h \
PersistentRevoluteLinkType.h \
PersistentRobot.h \
Point.h \
PrismaticLinkType.h \
QHSpinBox.h \
RevoluteLinkType.h \
RobotApp.h \
Robot.h \
RobotPosition.h \
TrajectoryApp.h \
Trajectory.h \
WLinkTypeCreation.h \
WLinkTypeSelection.h \
WLinkTypeView.h \
WMain.h \
WRobotConstruction.h \
WRobotCreation.h \
WRobotTrajectory.h \
WSelection.h \
WTrajectory.h \
WView.h
#The following line was inserted by qt3to4
QT +=  opengl qt3support 
