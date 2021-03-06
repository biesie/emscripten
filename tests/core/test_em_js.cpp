#include <emscripten.h>
#include <stdio.h>

EM_JS(void, noarg, (void), { out("no args works"); });
EM_JS(int, noarg_int, (void), {
  out("no args returning int");
  return 12;
});
EM_JS(double, noarg_double, (void), {
  out("no args returning double");
  return 12.25;
});
EM_JS(void, intarg, (int x), { out("  takes ints: " + x);});
EM_JS(void, doublearg, (double d), { out("  takes doubles: " + d);});
EM_JS(double, stringarg, (char* str), {
  out("  takes strings: " + Pointer_stringify(str));
  return 7.75;
});
EM_JS(int, multi_intarg, (int x, int y), {
  out("  takes multiple ints: " + x + ", " + y);
  return 6;
});
EM_JS(double, multi_mixedarg, (int x, const char* str, double d), {
  out("  mixed arg types: " + x + ", " + Pointer_stringify(str) + ", " + d);
  return 8.125;
});
EM_JS(int, unused_args, (int unused), {
  out("  ignores unused args");
  return 5.5;
});
EM_JS(double, skip_args, (int x, int y), {
  out("  skips unused args: " + y);
  return 6;
});
EM_JS(double, add_outer, (double x, double y, double z), {
  out("  " + x + " + " + z);
  return x + z;
});
EM_JS(int, user_separator, (void), {
  out("  can use <::> separator in user code");
  return 15;
});
EM_JS(int, user_comma, (void), {
  var x, y;
  x = {};
  y = 3;
  x[y] = [1, 2, 3];
  out("  can have commas in user code: " + x[y]);
  return x[y][1];
});

EM_JS(const char*, return_str, (void), {
  var jsString = 'hello from js';
  var lengthBytes = jsString.length+1;
  var stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes+1);
  return stringOnWasmHeap;
});

int main() {
  printf("BEGIN\n");
  noarg();
  printf("    noarg_int returned: %d\n", noarg_int());
  printf("    noarg_double returned: %f\n", noarg_double());

  intarg(5);
  doublearg(5.0675);
  printf("    stringarg returned: %f\n", stringarg("string arg"));
  printf("    multi_intarg returned: %d\n", multi_intarg(5, 7));
  printf("    multi_mixedarg returned: %f\n", multi_mixedarg(3, "hello", 4.75));
  printf("    unused_args returned: %d\n", unused_args(0));
  printf("    skip_args returned: %f\n", skip_args(5, 7));
  printf("    add_outer returned: %f\n", add_outer(5.5, 7.0, 14.375));
  printf("    user_separator returned: %d\n", user_separator());
  printf("    user_comma returned: %d\n", user_comma());

  printf("    return_str returned: %s\n", return_str());

  printf("END\n");
  return 0;
}
