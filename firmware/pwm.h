#ifndef PWM_H
#define PWM_H

void pwm_init(void);
void pwm_red(unsigned char brightness);
void pwm_green(unsigned char brightness);
void pwm_blue(unsigned char brightness);
void pwm_isr(void);

#endif /* PWM_H */
