#include <stdint.h>

struct robotburst_state {
  uint64_t output[4];
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
  uint64_t e;
  uint64_t f;
};

void robotburst(struct robotburst_state *s) {
  uint64_t mix = s->c ^ (s->d + s->e) ^ s->f;
  uint8_t i = 0;

  mix = ((mix << 43) | (mix >> 21)) + (s->a ^ s->b);
  mix = ((mix << 25) | (mix >> 39)) ^ (s->a + s->b);
  s->a = ((s->a << 27) | (s->a >> 37)) ^ s->b;
  s->b += 11111111111111111;
  s->c = ((s->c << 29) | (s->c >> 35)) + mix;
  s->e = ((s->e << 23) | (s->e >> 41)) ^ mix;
  mix = ((mix << 43) | (mix >> 21)) ^ (s->c + s->e);
  s->d = ((s->d << 41) | (s->d >> 23)) + s->a + mix;
  s->c = ((s->c << 27) | (s->c >> 37)) + s->b + s->d;
  s->d = ((s->d << 23) | (s->d >> 41)) ^ s->c;
  s->e = ((s->e << 39) | (s->e >> 25)) + s->f;
  s->f = ((s->f << 29) | (s->f >> 35)) ^ s->d;

  while (i < 2) {
    mix = s->d + s->e;
    s->c = ((s->c << 27) | (s->c >> 37)) + mix;
    s->f = ((s->f << 29) | (s->f >> 35)) ^ mix;
    mix = ((mix << 45) | (mix >> 19)) ^ s->c;
    s->c = ((s->c << 27) | (s->c >> 37)) + mix;
    s->d = ((s->d << 23) | (s->d >> 41)) ^ mix;
    mix = ((mix << 25) | (mix >> 39)) ^ s->f;
    s->e = ((s->e << 39) | (s->e >> 25)) + mix;
    s->f = ((s->f << 29) | (s->f >> 35)) ^ mix;
    i++;
  }

  s->output[0] = s->c + ((s->e << 27) | (s->e >> 37));
  s->output[1] = s->d + ((s->f << 23) | (s->f >> 41));
  s->output[2] = ((s->c << 25) | (s->c >> 39)) + (s->d ^ s->f);
  s->output[3] = (s->c ^ s->e) + ((s->d << 27) | (s->d >> 37));
}
