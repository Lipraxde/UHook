add_library(UHook SHARED UHook.cpp)

install(TARGETS UHook
        EXPORT UHookExports
        DESTINATION ${INSTALL_LIB_DIR}
)
