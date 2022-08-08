# Change to suit your system
LIBRARY_NAME=amsc
STATIC_LIBFILE=lib$(LIBRARY_NAME).a
DYNAMIC_LIBFILE=lib$(LIBRARY_NAME).so
# We need to link with the installed libraries
LDLIBS+=-L$(AMSC_LIB_DIR) -L. -l$(LIBRARY_NAME)

