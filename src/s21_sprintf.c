#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int res = s21_vsprintf(str, format, ap);
  va_end(ap);
  return res;
}

int s21_vsprintf(char *str, const char *format, va_list args) {
  char *out = str;
  const char *p = format;
  va_list v;
  va_copy(v, args);
  int written = 0;

  while (*p) {
    if (*p != '%') {
      *out++ = *p++;
      written++;
      continue;
    }
    p++;
    if (*p == '%') {
      *out++ = '%';
      written++;
      p++;
      continue;
    }
    s21_format_t f = {0};
    p = s21_parse_format(p, &f, &v);
    written += s21_format_value(&out, &f, &v);
  }
  *out = '\0';
  va_end(v);
  return written;
}

const char *s21_parse_format(const char *p, s21_format_t *fmt, va_list *args) {
  p = s21_parse_flags(p, fmt);
  p = s21_parse_width(p, fmt, args);
  p = s21_parse_precision(p, fmt, args);
  p = s21_parse_length(p, fmt);
  fmt->specifier = *p;
  return p + 1;
}

const char *s21_parse_flags(const char *p, s21_format_t *fmt) {
  const char *res = p;
  while (1) {
    if (*p == '-')
      fmt->flag_minus = true;
    else if (*p == '+')
      fmt->flag_plus = true;
    else if (*p == ' ')
      fmt->flag_space = true;
    else if (*p == '0')
      fmt->flag_zero = true;
    else if (*p == '#')
      fmt->flag_hash = true;
    else
      break;
    p++;
  }
  res = p;
  return res;
}

const char *s21_parse_width(const char *p, s21_format_t *fmt, va_list *args) {
  const char *res = p;
  if (*p == '*') {
    int w = va_arg(*args, int);
    if (w < 0) {
      fmt->flag_minus = true;
      fmt->width = -w;
    } else
      fmt->width = w;
    res = p + 1;
  } else {
    while (*p >= '0' && *p <= '9') {
      fmt->width = fmt->width * 10 + (*p++ - '0');
    }
    res = p;
  }
  return res;
}

const char *s21_parse_precision(const char *p, s21_format_t *fmt,
                                va_list *args) {
  const char *res = p;
  if (*p != '.') {
    res = p;
  } else {
    fmt->precision_specified = true;
    p++;
    if (*p == '*') {
      int pr = va_arg(*args, int);
      if (pr >= 0)
        fmt->precision = pr;
      else
        fmt->precision_specified = false;
      res = p + 1;
    } else {
      while (*p >= '0' && *p <= '9') {
        fmt->precision = fmt->precision * 10 + (*p++ - '0');
      }
      res = p;
    }
  }
  return res;
}

const char *s21_parse_length(const char *p, s21_format_t *fmt) {
  const char *res = p;
  if (*p == 'h' || *p == 'l' || *p == 'L') {
    fmt->length = *p;
    p++;
  }
  res = p;
  return res;
}

int s21_format_value(char **out, const s21_format_t *fmt, va_list *args) {
  int ret = 0;
  switch (fmt->specifier) {
    case 'd':
    case 'i':
      ret = s21_format_int(out, fmt, args);
      break;
    case 'u':
      ret = s21_format_unsigned(out, fmt, args);
      break;
    case 'o':
      ret = s21_format_octal(out, fmt, args);
      break;
    case 'x':
    case 'X':
      ret = s21_format_hex(out, fmt, args);
      break;
    case 'p':
      ret = s21_format_pointer(out, fmt, args);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      ret = s21_format_float(out, fmt, args);
      break;
    case 's':
      ret = s21_format_string(out, fmt, args);
      break;
    case 'c':
      ret = s21_format_char(out, args);
      break;
    case '%':
      **out = '%';
      (*out)++;
      ret = 1;
      break;
    default:
      ret = 0;
      break;
  }
  return ret;
}

int s21_int_to_str(long long v, char *buf, int precision) {
  unsigned long long val = v < 0 ? -v : v;
  int i = 0;
  int ret = 0;
  if (val == 0) {
    if (precision == 0) {
      buf[0] = '\0';
      ret = 0;
    } else {
      buf[i++] = '0';
      while (precision > i) buf[i++] = '0';
      s21_reverse(buf, i);
      buf[i] = '\0';
      ret = i;
    }
  } else {
    while (val) {
      buf[i++] = (char)('0' + val % 10);
      val /= 10;
    }
    while (precision > i) buf[i++] = '0';
    s21_reverse(buf, i);
    buf[i] = '\0';
    ret = i;
  }
  return ret;
}

int s21_uint_to_base(unsigned long long v, char *buf, int base, bool up,
                     int precision) {
  const char *d = up ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;
  int ret = 0;
  if (v == 0) {
    if (precision == 0) {
      buf[0] = '\0';
      ret = 0;
    } else {
      buf[i++] = '0';
      while (precision > i) buf[i++] = '0';
      s21_reverse(buf, i);
      buf[i] = '\0';
      ret = i;
    }
  } else {
    while (v) {
      buf[i++] = d[v % base];
      v /= base;
    }
    while (precision > i) buf[i++] = '0';
    s21_reverse(buf, i);
    buf[i] = '\0';
    ret = i;
  }
  return ret;
}

int s21_format_int(char **out, const s21_format_t *f, va_list *a) {
  long long v = (f->length == 'l') ? va_arg(*a, long) : va_arg(*a, int);
  char buf[64];
  int prec = f->precision_specified ? f->precision : -1;
  int len = s21_int_to_str(v, buf, prec);
  char sign = v < 0 ? '-' : f->flag_plus ? '+' : f->flag_space ? ' ' : 0;
  int total = len + (sign != 0);
  int pad = f->width > total ? f->width - total : 0;
  char p =
      (f->flag_zero && !f->flag_minus && !f->precision_specified) ? '0' : ' ';
  if (!f->flag_minus && p == ' ')
    while (pad--) *(*out)++ = ' ';
  if (sign) *(*out)++ = sign;
  if (!f->flag_minus && p == '0')
    while (pad--) *(*out)++ = '0';
  for (int i = 0; i < len; i++) *(*out)++ = buf[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > total ? f->width : total;
}

int s21_format_unsigned(char **out, const s21_format_t *f, va_list *a) {
  unsigned long long v = va_arg(*a, unsigned int);
  char buf[64];
  int prec = f->precision_specified ? f->precision : -1;
  int len = s21_uint_to_base(v, buf, 10, false, prec);
  int pad = f->width > len ? f->width - len : 0;
  char p =
      (f->flag_zero && !f->flag_minus && !f->precision_specified) ? '0' : ' ';
  if (!f->flag_minus)
    while (pad--) *(*out)++ = p;
  for (int i = 0; i < len; i++) *(*out)++ = buf[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > len ? f->width : len;
}

int s21_format_octal(char **out, const s21_format_t *f, va_list *a) {
  unsigned long long v = va_arg(*a, unsigned int);
  char buf[64];
  int prec = f->precision_specified ? f->precision : -1;
  int len = s21_uint_to_base(v, buf, 8, false, prec);
  if (f->flag_hash && v != 0) {
    for (int i = len; i >= 0; i--) buf[i + 1] = buf[i];
    buf[0] = '0';
    len++;
  }
  int pad = f->width > len ? f->width - len : 0;
  if (!f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  for (int i = 0; i < len; i++) *(*out)++ = buf[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > len ? f->width : len;
}

int s21_format_hex(char **out, const s21_format_t *f, va_list *a) {
  unsigned long long v = va_arg(*a, unsigned int);
  char buf[64];
  int prec = f->precision_specified ? f->precision : -1;
  int len = s21_uint_to_base(v, buf, 16, f->specifier == 'X', prec);
  int prefix = (f->flag_hash && v != 0) ? 2 : 0;
  int total = len + prefix;
  int pad = f->width > total ? f->width - total : 0;
  if (!f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  if (prefix) {
    *(*out)++ = '0';
    *(*out)++ = f->specifier;
  }
  for (int i = 0; i < len; i++) *(*out)++ = buf[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > total ? f->width : total;
}

int s21_format_pointer(char **out, const s21_format_t *f, va_list *a) {
  int result = 0;
  void *p = va_arg(*a, void *);
  if (!p) {
    const char *nil = "(nil)";
    int len = 5;
    int pad = f->width > len ? f->width - len : 0;
    if (!f->flag_minus)
      while (pad--) *(*out)++ = ' ';
    for (int i = 0; i < len; i++) *(*out)++ = nil[i];
    if (f->flag_minus)
      while (pad--) *(*out)++ = ' ';
    result = f->width > len ? f->width : len;
  } else {
    unsigned long long v = (uintptr_t)p;
    char buf[64];
    int len = s21_uint_to_base(v, buf, 16, false, -1);
    int total = len + 2;
    int pad = f->width > total ? f->width - total : 0;
    if (!f->flag_minus)
      while (pad--) *(*out)++ = ' ';
    *(*out)++ = '0';
    *(*out)++ = 'x';
    for (int i = 0; i < len; i++) *(*out)++ = buf[i];
    if (f->flag_minus)
      while (pad--) *(*out)++ = ' ';
    result = f->width > total ? f->width : total;
  }
  return result;
}

int s21_format_float(char **out, const s21_format_t *f, va_list *a) {
  double v =
      (f->length == 'L') ? (double)va_arg(*a, long double) : va_arg(*a, double);
  int prec = f->precision_specified ? f->precision : 6;
  char fmt[8], buf[512];
  snprintf(fmt, sizeof(fmt), "%%.%d%c", prec, f->specifier);
  int neg = v < 0;
  int len = snprintf(buf, sizeof(buf), fmt, fabs(v));
  char sign = neg ? '-' : f->flag_plus ? '+' : f->flag_space ? ' ' : 0;
  int total = len + (sign != 0);
  int pad = f->width > total ? f->width - total : 0;
  char p = (f->flag_zero && !f->flag_minus) ? '0' : ' ';
  if (!f->flag_minus && p == ' ')
    while (pad--) *(*out)++ = ' ';
  if (sign) *(*out)++ = sign;
  if (!f->flag_minus && p == '0')
    while (pad--) *(*out)++ = '0';
  for (int i = 0; i < len; i++) *(*out)++ = buf[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > total ? f->width : total;
}

int s21_format_string(char **out, const s21_format_t *f, va_list *a) {
  const char *s = va_arg(*a, const char *);
  if (!s) s = "(null)";
  int len = s21_strlen(s);
  if (f->precision_specified && f->precision < len) len = f->precision;
  int pad = f->width > len ? f->width - len : 0;
  if (!f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  for (int i = 0; i < len; i++) *(*out)++ = s[i];
  if (f->flag_minus)
    while (pad--) *(*out)++ = ' ';
  return f->width > len ? f->width : len;
}

int s21_format_char(char **out, va_list *a) {
  int ret = 0;
  *(*out)++ = (char)va_arg(*a, int);
  ret = 1;
  return ret;
}

void s21_reverse(char *s, int n) {
  for (int i = 0; i < n / 2; i++) {
    char t = s[i];
    s[i] = s[n - i - 1];
    s[n - i - 1] = t;
  }
}
