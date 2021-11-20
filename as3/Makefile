CC = gcc
TARGET = out
OBJ_DIR = .\obj

OBJECT_UTIL = dataSource.o\
		 stringUtil.o\

OBJECTS_STUDENT = student.o\
		 student_rbTree.o\
         studentRepository.o\
         studentService.o\

OBJECTS_REG= reg.o\
		 reg_rbTree.o\
         regRepository.o\
         regService.o

OBJECTS_CLAZZ= clazz.o\
		 clazz_rbTree.o\
         clazzRepository.o\
         clazzService.o

OBJECTS_COURSE= course.o\
		 course_rbTree.o\
         courseRepository.o\
         courseService.o\

OBJECTS_TREEINFO= treeInfo.o

OBJECTS_MODEL= transcript_model.o

OBJECTS_VIEW= viewTemplate.o\
		 credential.o\
		 login.o\
		 index.o\
		 transcript.o\
         delete.o\

OBJECTS_APP= appService.o\

OBJECTS = 

ifeq ($(T),)
 OBJECTS = app.o $(OBJECTS_APP) $(OBJECTS_STUDENT) $(OBJECTS_VIEW) $(OBJECTS_MODEL) $(OBJECTS_REG) $(OBJECTS_CLAZZ) $(OBJECTS_COURSE)
else ifeq ($(findstring student, $(T)), student)
 OBJECTS = $(OBJECTS_STUDENT)
else ifeq ($(findstring reg, $(T)), reg)
 OBJECTS = $(OBJECTS_REG) $(OBJECTS_STUDENT) $(OBJECTS_CLAZZ) $(OBJECTS_COURSE) $(OBJECTS_MODEL)
else ifeq ($(findstring clazz, $(T)), clazz)
 OBJECTS = $(OBJECTS_COURSE) $(OBJECTS_CLAZZ) 
else ifeq ($(findstring course, $(T)), course)
 OBJECTS = $(OBJECTS_COURSE)
else ifeq ($(findstring view, $(T)), view)
 OBJECTS = $(OBJECTS_VIEW)
else ifeq ($(findstring app, $(T)), app)
 OBJECTS = $(OBJECTS_APP) $(OBJECTS_STUDENT) $(OBJECTS_VIEW) $(OBJECTS_MODEL) $(OBJECTS_REG) $(OBJECTS_CLAZZ) $(OBJECTS_COURSE)
endif

ifneq ($(T),)
 OBJECTS += $(T).o
endif

OBJECTS += $(OBJECT_UTIL) $(OBJECTS_TREEINFO)

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(addprefix $(OBJ_DIR)/, $(OBJECTS))

#student
student.o :
	$(CC) -c -o $(OBJ_DIR)\student.o .\src\entity\student.c

student_rbTree.o :
	$(CC) -c -o $(OBJ_DIR)\student_rbTree.o .\src\rb_tree\student_rbTree.c

studentRepository.o :
	$(CC) -c -o $(OBJ_DIR)\studentRepository.o .\src\repository\studentRepository.c

studentService.o :
	$(CC) -c -o $(OBJ_DIR)\studentService.o .\src\service\studentService.c

#reg
reg.o :
	$(CC) -c -o $(OBJ_DIR)\reg.o .\src\entity\reg.c

reg_rbTree.o :
	$(CC) -c -o $(OBJ_DIR)\reg_rbTree.o .\src\rb_tree\reg_rbTree.c

regRepository.o :
	$(CC) -c -o $(OBJ_DIR)\regRepository.o .\src\repository\regRepository.c

regService.o :
	$(CC) -c -o $(OBJ_DIR)\regService.o .\src\service\regService.c


#clazz
clazz.o :
	$(CC) -c -o $(OBJ_DIR)\clazz.o .\src\entity\clazz.c

clazz_rbTree.o :
	$(CC) -c -o $(OBJ_DIR)\clazz_rbTree.o .\src\rb_tree\clazz_rbTree.c

clazzRepository.o :
	$(CC) -c -o $(OBJ_DIR)\clazzRepository.o .\src\repository\clazzRepository.c

clazzService.o :
	$(CC) -c -o $(OBJ_DIR)\clazzService.o .\src\service\clazzService.c

#course
course.o :
	$(CC) -c -o $(OBJ_DIR)\course.o .\src\entity\course.c

course_rbTree.o :
	$(CC) -c -o $(OBJ_DIR)\course_rbTree.o .\src\rb_tree\course_rbTree.c

courseRepository.o :
	$(CC) -c -o $(OBJ_DIR)\courseRepository.o .\src\repository\courseRepository.c

courseService.o :
	$(CC) -c -o $(OBJ_DIR)\courseService.o .\src\service\courseService.c

#treeInfo
treeInfo.o :
	$(CC) -c -o $(OBJ_DIR)\treeInfo.o .\src\rb_tree\treeInfo.c


#app
appService.o :
	$(CC) -c -o $(OBJ_DIR)\appService.o .\src\service\appService.c

viewTemplate.o :
	$(CC) -c -o $(OBJ_DIR)\viewTemplate.o .\src\view\viewTemplate.c

credential.o :
	$(CC) -c -o $(OBJ_DIR)\credential.o .\src\model\credential.c

#views
index.o :
	$(CC) -c -o $(OBJ_DIR)\index.o .\src\view\index.c

login.o :
	$(CC) -c -o $(OBJ_DIR)\login.o .\src\view\login.c

transcript.o :
	$(CC) -c -o $(OBJ_DIR)\transcript.o .\src\view\transcript.c

delete.o :
	$(CC) -c -o $(OBJ_DIR)\delete.o .\src\view\delete.c


#model
transcript_model.o :
	$(CC) -c -o $(OBJ_DIR)\transcript_model.o .\src\model\transcript_model.c

#dataSource
dataSource.o :
	$(CC) -c -o $(OBJ_DIR)\dataSource.o .\src\util\dataSource.c
	
stringUtil.o :
	$(CC) -c -o $(OBJ_DIR)\stringUtil.o .\src\util\stringUtil.c

#app
app.o :
	$(CC) -c -o $(OBJ_DIR)\app.o .\src\app.c

#target
$(T).o :
	$(CC) -c -o $(OBJ_DIR)\$(T).o .\test\$(T).c

run :
	.\$(TARGET)

clean :
	del $(OBJ_DIR)\*.o *.exe