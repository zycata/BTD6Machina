
// my_lib.cpp
extern "C" {
    __declspec(dllexport) int add(int a, int b) {
        return a + b;
    }
}
