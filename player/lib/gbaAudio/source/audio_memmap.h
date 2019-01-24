#define SOUND3_STEP32		(0<<5)	// Use two banks of 32 steps each
#define SOUND3_SET_BANK(n)	(n<<6)	// Bank to play 0 or 1 (non set bank is written to)
#define SOUND3_PLAY			(1<<7)	// Output sound

#define MEM_IO 0x04000000	//!< I/O registers
#define REG_BASE MEM_IO
#define REG_SNDSTAT *(volatile unsigned short*)(REG_BASE+0x0084)
#define SSTAT_ENABLE 0x0080	//!< Enable sound. NOTE: enable before using any other sound regs

#define REG_SNDDMGCNT *(volatile unsigned short*)(REG_BASE+0x0080)
#define REG_SNDDSCNT *(volatile unsigned short*)(REG_BASE+0x0082)

#define SDMG_SQR1		0x01
#define SDMG_SQR2		0x02
#define SDMG_WAVE		0x04
#define SDMG_NOISE		0x08

#define SDS_DMG100		0x0002	//!< Tone generators at 100% volume

//! \name Channel 1: Square wave with sweep
//\{
#define REG_SND1SWEEP		*(volatile unsigned short*)(REG_BASE+0x0060)	//!< Channel 1 Sweep
#define REG_SND1CNT			*(volatile unsigned short*)(REG_BASE+0x0062)	//!< Channel 1 Control
#define REG_SND1FREQ		*(volatile unsigned short*)(REG_BASE+0x0064)	//!< Channel 1 frequency
//\}

//! \name Channel 2: Simple square wave
//\{
#define REG_SND2CNT			*(volatile unsigned short*)(REG_BASE+0x0068)	//!< Channel 2 control
#define REG_SND2FREQ		*(volatile unsigned short*)(REG_BASE+0x006C)	//!< Channel 2 frequency
//\}

//! \name Channel 3: Wave player
//\{
#define REG_SND3SEL			*(volatile unsigned short*)(REG_BASE+0x0070)	//!< Channel 3 wave select
#define REG_SND3CNT			*(volatile unsigned short*)(REG_BASE+0x0072)	//!< Channel 3 control
#define REG_SND3FREQ		*(volatile unsigned short*)(REG_BASE+0x0074)	//!< Channel 3 frequency

#define REG_WAVE_RAM0		*(volatile unsigned int*)(REG_BASE+0x0090)
#define REG_WAVE_RAM1		*(volatile unsigned int*)(REG_BASE+0x0094)
#define REG_WAVE_RAM2		*(volatile unsigned int*)(REG_BASE+0x0098)
#define REG_WAVE_RAM3		*(volatile unsigned int*)(REG_BASE+0x009C)
//\}

//! \name Channel 4: Noise generator
//\{
#define REG_SND4CNT			*(volatile unsigned short*)(REG_BASE+0x0078)	//!< Channel 4 control
#define REG_SND4FREQ		*(volatile unsigned short*)(REG_BASE+0x007C)	//!< Channel 4 frequency
#define SND4_STAGES_7 0x0004
#define SND4_STAGES_15 0x0000
//\}

#define SSQR_DUTY1_2	0x0080	//!< 50% duty cycle (####----)

#define SSW_OFF         0x0008	//!< Disable sweep altogether

#define SFREQ_HOLD				 0	//!< Continuous play
#define SFREQ_TIMED			0x4000	//!< Timed play
#define SFREQ_RESET			0x8000	//!< Reset sound

#define SDMG_BUILD(_lmode, _rmode, _lvol, _rvol)	\
	( ((_rmode)<<12) | ((_lmode)<<8) | (((_rvol)&7)<<4) | ((_lvol)&7) )

#define SDMG_BUILD_LR(_mode, _vol) SDMG_BUILD(_mode, _mode, _vol, _vol)

#define SSQR_ENV_BUILD(ivol, dir, time)				\
	(  ((ivol)<<12) | ((dir)<<11) | (((time)&7)<<8) )

#define SSQR_BUILD(_ivol, dir, step, duty, len)		\
	( SSQR_ENV_BUILD(ivol,dir,step) | (((duty)&3)<<6) | ((len)&63) )
    