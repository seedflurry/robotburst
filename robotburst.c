#include <stdint.h>

struct robotburst256_state {
  uint64_t output[4];
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
  uint64_t e;
  uint64_t f;
};

void robotburst256(struct robotburst256_state *s) {
  uint64_t mix = (s->a + s->b) ^ (s->c ^ (s->d + s->e) ^ s->f);
  uint8_t i = 0;

  s->a = ((s->a << 29) | (s->a >> 35)) ^ s->b;
  s->b += 111111111111111;
  mix = ((mix << 45) | (mix >> 19)) ^ s->a;
  s->c = ((s->c << 29) | (s->c >> 35)) + mix;
  s->d = ((s->d << 39) | (s->d >> 25)) ^ mix;
  mix = ((mix << 25) | (mix >> 39)) ^ s->b;
  s->e = ((s->e << 23) | (s->e >> 41)) + mix;
  s->f = ((s->f << 27) | (s->f >> 37)) ^ mix;
  mix = (s->a + s->b) ^ (s->c ^ (s->d + s->e) ^ s->f);
  s->c = ((s->c << 37) | (s->c >> 27)) + mix;
  s->d = ((s->d << 41) | (s->d >> 23)) ^ mix;
  s->e = ((s->e << 25) | (s->e >> 39)) + mix;
  s->f = ((s->f << 35) | (s->f >> 29)) ^ mix;

  while (i < 4) {
    s->c = ((s->c << 27) | (s->c >> 37)) + s->d + 1;
    s->d = ((s->d << 23) | (s->d >> 41)) ^ s->e;
    s->e = ((s->e << 39) | (s->e >> 25)) + s->f + 1;
    s->f = ((s->f << 29) | (s->f >> 35)) ^ s->c;
    i++;
  }

  mix = (s->a + s->b) ^ (s->c ^ (s->d + s->e) ^ s->f);
  s->c = ((s->c << 27) | (s->c >> 37)) + mix;
  s->d = ((s->d << 23) | (s->d >> 41)) ^ mix;
  s->e = ((s->e << 39) | (s->e >> 25)) + mix;
  s->f = ((s->f << 29) | (s->f >> 35)) ^ mix;
  s->output[0] = s->c + ((s->e << 27) | (s->e >> 37));
  s->output[1] = (s->d ^ s->f) + s->e;
  s->output[2] = s->a + ((s->d << 27) | (s->d >> 37));
  s->output[3] = ((s->c << 25) | (s->c >> 39)) + s->f;
}
