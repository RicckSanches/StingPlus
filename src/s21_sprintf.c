#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  //   if (!str || !format) return result;
  va_list ap;
  va_start(ap, format);
  result = s21_vsprintf(str, format, ap);
  va_end(ap);
  return result;
}

int s21_vsprintf(char *str, const char *format, va_list args) {
  int written = 0;
  va_list v;
  va_copy(v, args);
  char *out = str;
  const char *p = format;
  while (*p) {
    if (*p == '%') {
      if (*(p + 1) == '%') {
        *out++ = '%';
        written++;
        p += 2;
        continue;
      } else if (*(p + 1) == '\0') {
        *out++ = '%';
        written++;
        p++;
        continue;
      }
      p++;
      s21_format_t f = {0};
      p = s21_parse_format(p, &f, &v);
      written += s21_format_value(&out, &f, &v);
    } else {
      *out++ = *p++;
      written++;
    }
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
  bool run = true;
  while (run) {
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
      run = false;
    if (run) p++;
  }
  return p;
}

const char *s21_parse_width(const char *p, s21_format_t *fmt, va_list *args) {
  if (*p == '*') {
    int w = va_arg(*args, int);
    if (w < 0) {
      fmt->flag_minus = true;
      fmt->width = -w;
    } else
      fmt->width = w;
    p++;
  } else {
    while (*p >= '0' && *p <= '9') {
      fmt->width = fmt->width * 10 + (*p - '0');
      p++;
    }
  }
  return p;
}

const char *s21_parse_precision(const char *p, s21_format_t *fmt,
                                va_list *args) {
  if (*p == '.') {
    fmt->precision_specified = true;
    p++;
    if (*p == '*') {
      int pr = va_arg(*args, int);
      if (pr >= 0)
        fmt->precision = pr;
      else
        fmt->precision_specified = false;
      p++;
    } else {
      while (*p >= '0' && *p <= '9') {
        fmt->precision = fmt->precision * 10 + (*p - '0');
        p++;
      }
    }
  }
  return p;
}

const char *s21_parse_length(const char *p, s21_format_t *fmt) {
  if (*p == 'h' || *p == 'l' || *p == 'L') {
    fmt->length = *p;
    p++;
  }
  return p;
}

int s21_format_value(char **out, const s21_format_t *fmt, va_list *args) {
  int w = 0;
  char s = fmt->specifier;
  if (s == 'd' || s == 'i')
    w = s21_format_int(out, fmt, args);
  else if (s == 'u')
    w = s21_format_unsigned(out, fmt, args);
  else if (s == 'o')
    w = s21_format_octal(out, fmt, args);
  else if (s == 'x' || s == 'X')
    w = s21_format_hex(out, fmt, args);
  else if (s == 'p')
    w = s21_format_pointer(out, fmt, args);
  else if (s == 'f' || s == 'e' || s == 'E' || s == 'g' || s == 'G')
    w = s21_format_float(out, fmt, args);
  else if (s == 's')
    w = s21_format_string(out, fmt, args);
  else if (s == 'c')
    w = s21_format_char(out, args);
  else if (s == '%') {
    **out = '%';
    (*out)++;
    w = 1;
  }
  return w;
}

int s21_format_int(char **out, const s21_format_t *fmt, va_list *args) {
  long long v;
  if (fmt->length == 'l')
    v = va_arg(*args, long);
  else if (fmt->length == 'h')
    v = (short)va_arg(*args, int);
  else
    v = va_arg(*args, int);
  char buf[64];
  int numlen =
      s21_int_to_str(v, buf, (fmt->precision_specified ? fmt->precision : 0));
  int sign_len = (v < 0) ? 1 : (fmt->flag_plus ? 1 : (fmt->flag_space ? 1 : 0));
  int total = numlen + sign_len;
  char pad = (fmt->flag_zero && !fmt->flag_minus && !fmt->precision_specified)
                 ? '0'
                 : ' ';
  int padcnt = (fmt->width > total) ? fmt->width - total : 0;
  if (!fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = pad;
      (*out)++;
    }
  if (v < 0) {
    **out = '-';
    (*out)++;
  } else if (fmt->flag_plus) {
    **out = '+';
    (*out)++;
  } else if (fmt->flag_space) {
    **out = ' ';
    (*out)++;
  }
  for (int i = 0; i < numlen; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  return (fmt->width > total) ? fmt->width : total;
}

int s21_format_unsigned(char **out, const s21_format_t *fmt, va_list *args) {
  unsigned long long v;
  if (fmt->length == 'l')
    v = va_arg(*args, unsigned long);
  else if (fmt->length == 'h')
    v = (unsigned short)va_arg(*args, unsigned int);
  else
    v = va_arg(*args, unsigned int);
  char buf[64];
  int len = s21_uint_to_base(v, buf, 10, false,
                             (fmt->precision_specified ? fmt->precision : 0));
  int total = len;
  char pad = (fmt->flag_zero && !fmt->flag_minus && !fmt->precision_specified)
                 ? '0'
                 : ' ';
  int padcnt = (fmt->width > total) ? fmt->width - total : 0;
  if (!fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = pad;
      (*out)++;
    }
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  return (fmt->width > total) ? fmt->width : total;
}

int s21_format_octal(char **out, const s21_format_t *fmt, va_list *args) {
  unsigned long long v;
  if (fmt->length == 'l')
    v = va_arg(*args, unsigned long);
  else if (fmt->length == 'h')
    v = (unsigned short)va_arg(*args, unsigned int);
  else
    v = va_arg(*args, unsigned int);
  char buf[64];
  int len = s21_uint_to_base(v, buf, 8, false,
                             (fmt->precision_specified ? fmt->precision : 0));
  if (fmt->flag_hash && v != 0) {
    char tmp[64];
    tmp[0] = '0';
    for (int i = 0; i < len; i++) tmp[i + 1] = buf[i];
    for (int i = 0; i <= len; i++) buf[i] = tmp[i];
    len += 1;
  }
  int total = len;
  char pad = (fmt->flag_zero && !fmt->flag_minus && !fmt->precision_specified)
                 ? '0'
                 : ' ';
  int padcnt = (fmt->width > total) ? fmt->width - total : 0;
  if (!fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = pad;
      (*out)++;
    }
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  return (fmt->width > total) ? fmt->width : total;
}

int s21_format_hex(char **out, const s21_format_t *fmt, va_list *args) {
  unsigned long long v;
  if (fmt->length == 'l')
    v = va_arg(*args, unsigned long);
  else if (fmt->length == 'h')
    v = (unsigned short)va_arg(*args, unsigned int);
  else
    v = va_arg(*args, unsigned int);
  bool up = (fmt->specifier == 'X');
  char buf[64];
  int len = s21_uint_to_base(v, buf, 16, up,
                             (fmt->precision_specified ? fmt->precision : 0));
  int prefix = (fmt->flag_hash && v != 0) ? 2 : 0;
  int total = len + prefix;
  char pad = (fmt->flag_zero && !fmt->flag_minus && !fmt->precision_specified)
                 ? '0'
                 : ' ';
  int padcnt = (fmt->width > total) ? fmt->width - total : 0;
  if (!fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = pad;
      (*out)++;
    }
  if (prefix) {
    **out = '0';
    (*out)++;
    **out = up ? 'X' : 'x';
    (*out)++;
  }
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  return (fmt->width > total) ? fmt->width : total;
}

int s21_format_pointer(char **out, const s21_format_t *fmt, va_list *args) {
  void *p = va_arg(*args, void *);
  unsigned long long v = (unsigned long long)(uintptr_t)p;
  char buf[64];
  int len = s21_uint_to_base(v, buf, 16, false, 0);
  int total = len + 2;
  int padcnt = (fmt->width > total) ? fmt->width - total : 0;
  if (!fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  **out = '0';
  (*out)++;
  **out = 'x';
  (*out)++;
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < padcnt; i++) {
      **out = ' ';
      (*out)++;
    }
  return (fmt->width > total) ? fmt->width : total;
}

int s21_format_float(char **out, const s21_format_t *fmt, va_list *args) {
  char tmp[64];
  int pos = 0;
  tmp[pos++] = '%';
  if (fmt->flag_minus) tmp[pos++] = '-';
  if (fmt->flag_plus) tmp[pos++] = '+';
  if (fmt->flag_space) tmp[pos++] = ' ';
  if (fmt->flag_zero) tmp[pos++] = '0';
  if (fmt->flag_hash) tmp[pos++] = '#';
  if (fmt->width)
    pos += snprintf(tmp + pos, (int)(sizeof tmp - pos), "%d", fmt->width);
  if (fmt->precision_specified)
    pos += snprintf(tmp + pos, (int)(sizeof tmp - pos), ".%d", fmt->precision);
  tmp[pos++] = fmt->specifier;
  tmp[pos] = '\0';
  char buf[256];
  if (fmt->length == 'L') {
    long double ld = va_arg(*args, long double);
    snprintf(buf, sizeof buf, tmp, ld);
  } else {
    double d = va_arg(*args, double);
    snprintf(buf, sizeof buf, tmp, d);
  }
  int len = s21_strlen(buf);
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  return len;
}

int s21_format_string(char **out, const s21_format_t *fmt, va_list *args) {
  const char *s = va_arg(*args, const char *);
  if (!s) s = "(null)";
  int len = s21_strlen(s);
  if (fmt->precision_specified && fmt->precision < len) len = fmt->precision;
  char pad = (fmt->flag_zero) ? '0' : ' ';
  s21_apply_width(out, s, len, fmt, pad);
  return (fmt->width > len) ? fmt->width : len;
}

int s21_format_char(char **out, va_list *args) {
  int c = va_arg(*args, int);
  **out = (char)c;
  (*out)++;
  return 1;
}

int s21_strlen(const char *str) {
  int i = 0;
  while (str && str[i]) i++;
  return i;
}

void s21_reverse(char *str, int len) {
  for (int i = 0; i < len / 2; i++) {
    char t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
  }
}

int s21_int_to_str(long long value, char *buf, int precision) {
  int i = 0;
  unsigned long long v =
      (value < 0) ? (unsigned long long)(-value) : (unsigned long long)value;
  if (v == 0) buf[i++] = '0';
  while (v) {
    buf[i++] = (char)('0' + (v % 10));
    v /= 10;
  }
  while (i < precision) buf[i++] = '0';
  s21_reverse(buf, i);
  return i;
}

int s21_uint_to_base(unsigned long long value, char *buf, int base,
                     bool uppercase, int precision) {
  int i = 0;
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  if (value == 0) buf[i++] = '0';
  while (value) {
    buf[i++] = digits[value % base];
    value /= base;
  }
  while (i < precision) buf[i++] = '0';
  s21_reverse(buf, i);
  return i;
}

void s21_apply_width(char **out, const char *buf, int len,
                     const s21_format_t *fmt, char pad_with) {
  int pad = fmt->width > len ? fmt->width - len : 0;
  if (!fmt->flag_minus) {
    char ch = (fmt->flag_zero) ? pad_with : ' ';
    for (int i = 0; i < pad; i++) {
      **out = ch;
      (*out)++;
    }
  }
  for (int i = 0; i < len; i++) {
    **out = buf[i];
    (*out)++;
  }
  if (fmt->flag_minus)
    for (int i = 0; i < pad; i++) {
      **out = ' ';
      (*out)++;
    }
}
