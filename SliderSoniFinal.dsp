// // // // // // // // // // // // // // // // // // // // // // // // // // // // D E F I N I T I O N S // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
import("stdfaust.lib");
// Panner
NUM_PANPOS = 7;
// Dotted Delay
DOTDEL_FC_HP = 800;					DOTDEL_FC_LP = 2000;
// FM Synth
FM_DISTMIX = 0.05;
// Piano Single Note
PIANO_WAVEWIDTH1 = 33;				PIANO_WAVEWIDTH2 = 10;					PIANO_WAVEWIDTH3 = 66;
// Full Chord Synth			
CS_DEL_N1 = 0.015;					CS_DEL_N2 = 0.030;						CS_DEL_N3 = 0.045;		

// MUSIC Trackwise SYNTH //
// 1, 2, 3, 8 are sample-based
// 4 - CHORD SYNTH
PANPOS_NOTES = 3,4,5,6;
AT_C = 0.001;			RL_C = 1;					FV_C = 1;
// MALLET FM
MALLET_MRATIO = 2;		MALLET_I_FIXED = 2.4;	MALLET_I_ENV = 6.86;	MALLET_A = 0.001;	MALLET_D = 0.001;	MALLET_S = 0.5;		MALLET_R = 0.4;			MALLET_ENVTYPE = 0;
// 5 - BASSLINE
AT_R = 0.001;			RL_R = 0.6 + (tempo < 120)*(120-tempo)*0.06;
MOD_NUM_R = 5;			FREQ_FACTOR_R = 3;		MOD_DEPTH_R = 35;
// BASSLINE FM
BASSLINE_MRATIO = 2;	BASSLINE_I_FIXED = 6.75;	BASSLINE_I_ENV = 7.46;		BASSLINE_A = 0.007; 	BASSLINE_D = 0.001;		BASSLINE_S = 0.6553;		BASSLINE_R = 0.65;
BASSLINE_ENVTYPE = 1;
// AGGRO FM
AGGRO_MRATIO = 3;		AGGRO_I_FIXED = 10;	AGGRO_I_ENV = 10;		AGGRO_A = 0.01;	AGGRO_D = 0.0001;	AGGRO_S = 0.5;	AGGRO_R = 0.867;		AGGRO_ENVTYPE = 1;
// 6 - MAIN MELODY
AT_M = 0.001;							RL_M = 4;
FB_DEL_M = 0.5;							WET_DEL_M = 0.8;
FC_LP_M = 20000;						G_SIN_M = -90;				G_NS_M = -90;				RL_NS_M = 0.05;			FC_HP_NS_M = 3000;
// TRUMPETISH FM
TRUMPET_MRATIO = 1;		TRUMPET_I_FIXED = 10;	TRUMPET_I_ENV = 10;		TRUMPET_A = 0.05;	TRUMPET_D = 0.0001;	TRUMPET_S = 0.5;	TRUMPET_R = 0.78;		TRUMPET_ENVTYPE = 1;
// 7
AT_CS = 0.001;							RL_CS = 5;
FB_DEL_CS = 0.8;						WET_DEL_CS = 0.4;
DMP_KS_CS = 0.99;						FREQ_OFFSET_LR = 0.7;

//Sonifications
LIST_FREQ_DISTFACTORS = 0.05,-0.03,0.31,-0.27;																// CHORD FREQ DIST FACTORS
SONI_SB_Z2_ONOFF = waveform {1, 1, 1, 1, 0, 0,		1, 1, 1, 0, 0, 1,		1, 1, 1, 0, 1, 0,		1, 1, 0, 0, 0, 0,			
				   			 1, 1, 0, 0, 0, 0,		1, 0, 0, 0, 0, 0,		1, 1, 0, 0, 0, 0,		1, 1, 1, 0, 0, 1};

Soni_R1_MaxDelSec(trackIndex) = 0.1,0.17,0.23,0.29,0.37,0.47,0.59,0.71 : ba.selectn(8,trackIndex);
SONI_SB_Z2_ONOFF_RD(i) = SONI_SB_Z2_ONOFF,i : rdtable;

Soni_R1_maxLevel = 0;	Soni_R1_minLevel = -80;																// INSTRUMENTATION
Soni_R3_1_Fc_Max = 10000; Soni_R3_1_Fc_Min = 200;																// BRIGHTNESS
Soni_R3_2_Fc_Max = 3000; Soni_R3_2_Fc_Min = 200;																// BRIGHTNESS

Soni_J1_MaxWarpFactor = 10;											// TONIC PITCH 
Soni_J2_minFreq = 250;		Soni_J2_maxFreq = 5000;					// PITCHED WAVE
Soni_J3_minFreq = 1000;		Soni_J3_maxFreq = 20000;				// WHOOSH NOISE
Soni_J3_HPF_FC = 150;		Soni_J3_LPF_Q = 5;						// "

// BUSS REVERB
REV_MST_PDEL_MS = 10;												// PRE-DELAY
REV_MST_F_DC_MID = 100;												// DC/MID CROSSOVER FREQ
REV_MST_F_MID_HI = 2000;											// MID/HI CROSSOVER FREQ
REV_MST_T60_DC = 1;													// RT60 - DC
REV_MST_FsMax = 48000;												// FS MAX
REV_MST_HPF_FC = 200;												// FC - LOWER
REV_MST_LPF_FC = 3500;												// FC - UPPER

// REVERB SENDS
REV_SND = -8,-10,-5,0,-5;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // U S E R  I N T E R F A C E // // // // // // // // // // // // // // // // // // // // // // // // // // //
// TABS
musicInfoTab(x) = tgroup("Mapping_Tabs",hgroup("Music_Info",x));
compTab(x) = tgroup("Mapping_Tabs",vgroup("Comp_Section",x));
eqTab(x) = tgroup("Mapping_Tabs",vgroup("EQ_Section",x));
sonificationTab(x) = tgroup("Mapping_Tabs",hgroup("Sonification Types",x));
mixMasterTab(x) = tgroup("Mapping_Tabs",hgroup("Mixer_And_Master",x));
traditionalSoni(x) = sonificationTab(vgroup("Traditional_Strategies",x));

// SLIDER GROUPS
// MUSIC INFO TAB
pitchInfo(x) = musicInfoTab(vgroup("Pitch",x));
accentInfo(x) = musicInfoTab(vgroup("Accent",x));
velocityInfo(x) = musicInfoTab(vgroup("Velocity",x));
// MIX AND MASTER TAB
trackGainGroup(x) = mixMasterTab(vgroup("Track Gain",x));
trackMuteGroup(x) = mixMasterTab(vgroup("Track Mute",x));
masterGainGroup(x) = mixMasterTab(vgroup("Master Gain",x));
masterEQGroup(x) = mixMasterTab(vgroup("Master EQ",x));
variantGroup(x) = mixMasterTab(vgroup("Track Variant",x));
// EQ TAB
eqTrackGroup(i,x) = eqTab(hgroup("Track %i",x));
// COMP TAB
compTrackGroup(i,x) = compTab(hgroup("Track %i",x));

// Tempo and Fluidity
tempo = musicInfoTab(vslider("Tempo",120,50,150,0.1)) : limit(60,150);
fluidity = musicInfoTab(vslider("Fluidity",1,0.05,10,0.01)) : limit(0.2,5);

// Traditional Soni
sonificationType = checkbox("Traditional");
Soni_X_Trad = traditionalSoni(hslider("x_Traditional",0,0,1,0.001)) : si.smoo;
Soni_Choice_Trad = traditionalSoni(hslider("Choice_Traditional",0,0,4,1)); 

//Variants
VAR_1 = variantGroup(nentry("Variant_1",1,1,3,1));
VAR_2 = variantGroup(nentry("Variant_2",1,1,3,1));
VAR_3 = variantGroup(nentry("Variant_3",1,1,3,1));
VAR_4 = variantGroup(nentry("Variant_4",1,1,3,1));
VAR_5 = variantGroup(nentry("Variant_5",1,1,3,1));
VAR_6 = variantGroup(nentry("Variant_6",1,1,3,1));
VAR_7 = variantGroup(nentry("Variant_7",1,1,3,1));
VAR_8 = variantGroup(nentry("Variant_8",1,1,3,1));

//Music Info
																						// NOTE NUMBERS
KEYNUM_C_1 = pitchInfo(hslider("T4_P_1",100,20,10000,0.001));									// 4-1
KEYNUM_C_2 = pitchInfo(hslider("T4_P_2",100,20,10000,0.001));									// 4-2
KEYNUM_C_3 = pitchInfo(hslider("T4_P_3",100,20,10000,0.001));									// 4-3
KEYNUM_C_4 = pitchInfo(hslider("T4_P_4",100,20,10000,0.001));									// 4-4
KEYNUM_R = pitchInfo(hslider("T5_P_1",100,20,10000,0.001));										// 5
KEYNUM_M = pitchInfo(hslider("T6_P_1",100,20,10000,0.001));										// 6
KEYNUM_CS_1 = pitchInfo(hslider("T7_P_1",100,20,10000,0.001));									// 7-1
KEYNUM_CS_2 = pitchInfo(hslider("T7_P_2",100,20,10000,0.001));									// 7-2
KEYNUM_CS_3 = pitchInfo(hslider("T7_P_3",100,20,10000,0.001));									// 7-3
KEYNUM_CS_4 = pitchInfo(hslider("T7_P_4",100,20,10000,0.001));									// 7-4

//Accent Info
ACC_M = accentInfo(hslider("T6_A_1",5,0,9,0.01));												// 6
ACC_C_1 = accentInfo(hslider("T4_A_1",5,0,9,0.01));												// 4-1
ACC_C_2 = accentInfo(hslider("T4_A_2",5,0,9,0.01));												// 4-2
ACC_C_3 = accentInfo(hslider("T4_A_3",5,0,9,0.01));												// 4-3
ACC_C_4 = accentInfo(hslider("T4_A_4",5,0,9,0.01));												// 4-4
ACC_R = accentInfo(hslider("T5_A_1",5,0,9,0.01));												// 5
																								// VELOCITIES
V_K = velocityInfo(hslider("T1_V_1",9,0,9,0.1));													// 1
V_S = velocityInfo(hslider("T2_V_1",9,0,9,0.1));													// 2
S_FNUM = ((V_S > 3) + (V_S > 6)) : ba.sAndH(V_S*TRG_S);											// Snare - File Number
V_HH = velocityInfo(hslider("T3_V_1",9,0,9,0.1)); 												// 3
HH_FNUM = ((V_HH > 3) + (V_HH > 6)) : ba.sAndH(V_HH*TRG_HH);									// HH - File Number
V_C_1 = velocityInfo(hslider("T4_V_1",9,0,9,0.1));												// 4-1
V_C_2 = velocityInfo(hslider("T4_V_2",9,0,9,0.1));												// 4-2
V_C_3 = velocityInfo(hslider("T4_V_3",9,0,9,0.1));												// 4-3
V_C_4 = velocityInfo(hslider("T4_V_4",9,0,9,0.1));												// 4-4
V_LIST_C = V_C_1, V_C_2, V_C_3, V_C_4;															// 4 - LIST
V_R = velocityInfo(hslider("T5_V_1",9,1,9,0.1));													// 5
V_M = velocityInfo(hslider("T6_V_1",9,1,9,0.1));													// 6
V_CS = velocityInfo(hslider("T7_V_1",9,0,9,0.1));												// 7
V_CR = velocityInfo(hslider("T8_V_1",9,0,9,0.1));												// 8

//Sonification Sliders and Preprocessing
soniSlider(idx,defaultVal) = sonificationTab(vgroup("AP Values",hslider("Soni %idx",defaultVal,0,1,0.001)));

// TRADITIONAL
X_T_Pitch =							soniSlider(1,0);									
X_T_Tempo =							soniSlider(2,0);									
X_T_Synchronicity = 				soniSlider(3,0);									
X_T_Harmonicity = 					soniSlider(4,0);									
X_T_Brightness =			 		soniSlider(5,0);

// MUSICAL
X_M_MelDegree =						soniSlider(6,0);									
X_M_Tempo =							soniSlider(7,0);									
X_M_Synchronicity = 				soniSlider(8,0);									
X_M_Harmonicity = 					soniSlider(9,0);									
X_M_Brightness =			 		soniSlider(10,0);									

SONI_GAIN_DB = masterGainGroup(vslider("Soni Buss Gain",-8,-10,2,0.01));
masterGain = masterGainGroup(vslider("Master Gain",-6,-96,12,0.01) : ba.db2linear);

// // // // // // // // // // // // // // // // // // // // // // // // // // // // F U N C T I O N S // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
// UTILITY
BT_SMPL = ba.tempo(tempo);
stereoLinGain(gain) = _,_ : *(gain),*(gain);
stereodBGain(gain) = _,_ : *(linGain),*(linGain) with { linGain = ba.db2linear(gain); };
stereoLinMult(gainPair) = _,_ : *(gainPair : select2(0)),*(gainPair : select2(1));
stereoEffect(effect) = _,_ : effect,effect;
limit(lower,higher) = _ : max(lower) : min(higher);
hard_clip(limit) = _ : min(limit) : max(-1*limit) : _;

// CONVERT VELOCITY VALUE TO TRIGGER ON CHANGE
velToTrigger(vel) = trigger with
{
  trigger = (posTrig + negTrig);
  posTrig = vel : ba.impulsify;
  negTrig = - 1 * (vel) : ba.impulsify : *(vel > 0);
};

// CONVERT 0-10 VELOCITY VALUE TO MONO GAIN MULTIPLIER
applyVelocity(velocity,trigger,maxVel) = _ : *(gainMult)	 with
{
  sampledVel = velocity : ba.sAndH(trigger);
  dBGain = (sampledVel - 10) * 26.0 / 9.0;
  gainMult = ba.db2linear(dBGain);
};

// TEMPO-BASED INSTRUMENT RELEASE FACTOR
tempo_RelFactor = fluidity + 1.5 * (120-tempo) / 40 * (tempo < 120);

// MASTER LIMITER
masterLimiter(ipGaindB) = _ : compLimiter(ipGaindB,10,0,0.001,0.05,0.050);

// SHORT STRUM DELAY
shortDelay(d_ms) = stereoEffect(de.fdelay(5000,d_ms*ma.SR));

// CHANNEL PROCESSORS - MONO AND STEREO
monoChannel(trackIndex) = *(0.25) : channelComp(compTrackGroup(trackIndex)) : parametricEQ(eqTrackGroup(trackIndex));
stereoChannel(trackIndex) = stereoLinGain(0.25) : stereoEffect(channelComp(compTrackGroup(trackIndex))) : stereoEffect(parametricEQ(eqTrackGroup(trackIndex)));

// PREPROCESS CHORD FREQUENCIES
getChordFinalFreqs(LIST) = freqs with 
{   
  freqs = par(i,4,freq(i));																							// CREATE FREQ LIST
  freq(i) = freqs_pre(i) : *(Soni_P3_freqDistFactor(i));									// APPLY TUNING SONIFICATIONS
  Soni_P3_freqDistFactor(i) = LIST_FREQ_DISTFACTORS : ba.selectn(4,i) : *(X_M_Harmonicity) : +(1);			// CALCULATE CHORD DIST AMOUNT
  freqs_pre(i) = LIST : ba.selectn(4,i);																			// GET INDIVIDUAL MIDI KEYS
};

// GET STEREO PAN GAINS
getPanFunction(panIndex) = panFunction	with	
{
  panFunction = _ <: _*(L_multiplier), _*(R_multiplier);																			// SPLIT AND MULTIPLY
  L_multiplier = 1,0.95,0.3,0.9,0.8,0.6,0.4 : ba.selectn(NUM_PANPOS,panIndex);														// L-MULTIPLIER
  R_multiplier = 1,0.3,0.95,0.4,0.6,0.8,0.9 : ba.selectn(NUM_PANPOS,panIndex);														// R-MULTIPLIER											
};

// CHANNEL COMP
channelComp(compTrackGroup) = compLimiter(0,ratio,thresh,att,rel,0.050)	 with	{
  ratio = compTrackGroup(hslider("Ratio[style:knob]",1,1,10,0.1));
  thresh = compTrackGroup(hslider("Threshold[style:knob]",0,-96,0,0.1));
  att = compTrackGroup(hslider("Attack[style:knob]",0.1,0.001,0.5,0.001));
  rel = compTrackGroup(hslider("Release[style:knob]",0.1,0.001,0.5,0.001));		};

// CHANNEL EQ
parametricEQ(eqTrackGroup) = fi.resonhp(fc_HP,Q_HP,1) : fi.peak_eq_cq(gain_P1,f_P1,Q_P1) : fi.peak_eq_cq(gain_P2,f_P2,Q_P2) : fi.resonlp(fc_LP,Q_LP,1)
  with	{ hpGroup(x) = hgroup("1_HPF",x);
  p1Group(x) = hgroup("2_Parametric_1",x);
  p2Group(x) = hgroup("3_Parametric_2",x);
  lpGroup(x) = hgroup("4_LPF",x);
  fc_HP = eqTrackGroup(hpGroup(hslider("Freq[style:knob]",50,50,1000,0.1)));
  Q_HP = eqTrackGroup(hpGroup(hslider("Q[style:knob]",0.7,0.5,10,0.01)));
  fc_LP = eqTrackGroup(lpGroup(hslider("Freq[style:knob]",20000,50,20000,0.1)));
  Q_LP = eqTrackGroup(lpGroup(hslider("Q[style:knob]",0.7,0.5,10,0.01)));
  gain_P1 = eqTrackGroup(p1Group(hslider("Gain[style:knob]",0,-24,24,0.01)));
  f_P1 = eqTrackGroup(p1Group(hslider("Freq[style:knob]",500,100,2000,0.01)));
  Q_P1 = eqTrackGroup(p1Group(hslider("Q[style:knob]",0.7,0.5,10,0.01)));
  gain_P2 = eqTrackGroup(p2Group(hslider("Gain[style:knob]",0,-24,24,0.01)));
  f_P2 = eqTrackGroup(p2Group(hslider("Freq[style:knob]",2000,1500,15000,0.01)));
  Q_P2 = eqTrackGroup(p2Group(hslider("Q[style:knob]",0.7,0.5,10,0.01))); };

// 3 - Effects
// Dotted Delay
dotted_delay(feedback,delay,wet) = +~(de.delay(100000,del) : filt)*feedback*wet :> _	with	{ filt = fi.bandpass(2,DOTDEL_FC_HP,DOTDEL_FC_LP); del = 0.75*delay; };

// Compressor-Limiter
compLimiter(inputGain_dB,ratio,thresh,att,rel,kneeAtt) = _*inputGain_lin 
  <: _*(an.amp_follower_ud(att,rel) : ba.linear2db : outminusindb : kneesmooth : ba.db2linear)
with{inputGain_lin = ba.db2linear(inputGain_dB);
	 outminusindb(level) = max(level-thresh,0)*(1/ratio - 1);													// CALCULATE GAIN REDUCTION
	 kneesmooth = si.smooth(ba.tau2pole(kneeAtt));	};															// SMOOTH KNEE

// Master COMP
masterComp = stereoEffect(compLimiter(0,1.01,-20,100,300,0.05)) : stereoEffect(compLimiter(0,1.1,-5,50,200,0.05)) : stereodBGain(2);

//Reverb Master
reverbMaster = _,_ <: re.zita_rev1_stereo(REV_MST_PDEL_MS,REV_MST_F_DC_MID,REV_MST_F_MID_HI,REV_MST_T60_DC,rt_60,REV_MST_FsMax) : filter
with {
  rt_60 = min(0.3 + (150 - tempo) * 0.05,1.85); 																			// TEMPO DEPENDENT RT60
  filter = stereoEffect(fi.bandpass(1,REV_MST_HPF_FC,REV_MST_LPF_FC));														// OUTPUT FILTER
};

stereoMasterSection(trackIndex) = stereoOut
  with
{
  stereoOut = stereoLinGain(trackGain) : stereoLinGain(1-trackMute);
  trackGain = trackGainGroup(hslider("Track %trackIndex",0,-96,24,0.01) : ba.db2linear);
  trackMute = trackMuteGroup(checkbox("%trackIndex"));
};

//4 - Synthesis
samplePlayer(fileFunc,trigger) = fileFunc(ba.countup(96000,trigger));
K_FILES = soundfile("K_SMPL[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\K_V1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\K_V2.wav';
										'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\K_V3.wav'}]",1) : !,!,_;
S_V1_FILES = soundfile("S_SMPL_V1[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V1_1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V1_2.wav';
									   'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V1_3.wav'}]",1) : !,!,_;
S_V2_FILES = soundfile("S_SMPL_V2[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V2_1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V2_2.wav';
									   'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V2_3.wav'}]",1) : !,!,_;
S_V3_FILES = soundfile("S_SMPL_V3[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V3_1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V3_2.wav';
									   'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\S_V3_3.wav'}]",1) : !,!,_;
CR_FILES = soundfile("CR_SMPL[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\CR_V1.wav'; 	     'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\CR_V2.wav';
									   'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\CR_V3.wav'}]",1) : !,!,_;
HH_V1_FILES = soundfile("HH_SMPL_V1[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V1_1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V1_2.wav';
										'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V1_3.wav'}]",1) : !,!,_;
HH_V2_FILES = soundfile("HH_SMPL_V2[url:{'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V2_1.wav'; 'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V2_2.wav';
										'D:\\\\GaitSonification\\\\Drum Samples\\\\Final Library\\\\HH_V2_3.wav'}]",1) : !,!,_;

K_SMPL_V1(i) =   0,i : K_FILES;			K_SMPL_V2(i) =   1,i : K_FILES;			K_SMPL_V3(i) =   2,i : K_FILES;
S_SMPL_V1_1(i) = 0,i : S_V1_FILES;		S_SMPL_V1_2(i) = 1,i : S_V1_FILES;		S_SMPL_V1_3(i) = 2,i : S_V1_FILES;
S_SMPL_V2_1(i) = 0,i : S_V2_FILES;		S_SMPL_V2_2(i) = 1,i : S_V2_FILES;		S_SMPL_V2_3(i) = 2,i : S_V2_FILES;
S_SMPL_V3_1(i) = 0,i : S_V3_FILES;		S_SMPL_V3_2(i) = 1,i : S_V3_FILES;		S_SMPL_V3_3(i) = 2,i : S_V3_FILES;
CR_SMPL_V1(i) = 0,i : CR_FILES;			CR_SMPL_V2(i) = 1,i : CR_FILES;			CR_SMPL_V3(i) = 2,i : CR_FILES;
HH_SMPL_V1_1(i) = 0,i : HH_V1_FILES;	HH_SMPL_V1_2(i) = 1,i : HH_V1_FILES;	HH_SMPL_V1_3(i) = 2,i : HH_V1_FILES;
HH_SMPL_V2_1(i) = 0,i : HH_V2_FILES;	HH_SMPL_V2_2(i) = 1,i : HH_V2_FILES;	HH_SMPL_V2_3(i) = 2,i : HH_V2_FILES;

fmSynth_Versatile(fc,modRatio,I_fixed,I_ampDependent,a,d,s,r,envType,trigger,vel,acc) = output
  with
{
  fc_cooked = fc : si.smooth(ba.tau2pole(0.005));
  acc_cooked = 1 + (acc-5.0)/5.0;
  output = os.osc(fc_cooked + dev) * ampEnv;
  dev = I * ampEnv * modFreq * os.triangle(modFreq);
  I = I_fixed + (I_ampDependent * acc_cooked * (0.5 + velFactor) + I_freq) * (ampEnv);
  I_freq = 4 * (fc - 300)/300;
  modFreq = (modRatio + X_M_Harmonicity) * fc_cooked;
  release_basic = ba.tempo(ba.tempo(tempo))/ma.SR * (1 + velFactor * 2);
  env_basic = en.ar(a,release_basic,trigger);
  triggerCooked = (env_basic > 0.5) + (env_basic > env_basic');
  chosenEnv = en.adsr(a,d,s,r*tempo_RelFactor,triggerCooked),
  			  en.adsre(a,d,s,r*tempo_RelFactor,triggerCooked),
  			  en.ar(a,r*tempo_RelFactor,trigger), 
  			  en.are(a,r*tempo_RelFactor,trigger),
  			  en.arfe(a,r*tempo_RelFactor,0.3,trigger) : ba.selectn(5,envType); 
  ampEnv = chosenEnv : si.smooth(ba.tau2pole(a));
  velFactor = 1 : applyVelocity(vel,trigger,9);
};

leadSynth(fundamental,synthFunc,velocity,trigger,synthRelease,synthCutoff,acc) = output
with
{																			
  output = melSynth,melSynth;																					// OUTPUT SUMMING
  melSynth = synthFunc(fundamentalCooked) * env : applyVelocity(velocity,trigger,9);							// MEL COMPONENT
  fundamentalCooked = 2 * fundamental * soniVibratoLFO * accVibrato : limit(20,5000);
  env = en.ar(0.001,synthRelease * tempo_RelFactor,trigger);													// MEL ENVELOPE
vibLFO = os.osc(tempo/15);
  accVibrato = 1 + (0.00045 * acc * vibLFO) : si.smooth(ba.tau2pole(0.001));
  soniVibratoLFO = 1 + X_M_Harmonicity * vibLFO * 0.5 : si.smoo;								// CF DIST SONI - VIBRATO LFO
};

fmSynth(fundamental,numMod,freqFactor,release,depth,trigger) = (fmSynth + dirtyBus) * env 	with
{ 
  fmSynth = sy.fm(freqList,depthList);																			// SYNTH - FM 
  dirtyBus = fmSynth : ef.cubicnl(0.7,0) : _ *(FM_DISTMIX);														// DIST MIX
  freqList = par(i,numMod,fundamental * pow(freqFactor,i));														// (1)CARRIER + MOD FREQ LIST
  depthList = par(i,numMod-1,depthCooked);																		// MOD DEPTH LIST
  depthCooked = depth * env * 9;																				// COOKED DEPTH
  env = sqrt(en.ar(0.001,release * tempo_RelFactor, trigger)) : si.smooth(ba.tau2pole(0.001));					// AMP ENVELOPE
};

pulseWave(freq,widthPercent) = output with
{
  output = 2 * (ba.pulsen(duration,interval) - 0.5);															// DC CORRECTED OUTPUT WAVE
  duration = widthPercent * interval / 100;																		// PULSE UP TIME
  interval = ma.SR / freq;																						// PUlSE TOTAL PERIOD
};

pianoSim_singleNote(freq,trigger,acc) = monoOut
  with
{
  monoOut = pulseWave(freq,PIANO_WAVEWIDTH1),pulseWave(freq,
			PIANO_WAVEWIDTH2),pulseWave(freq,PIANO_WAVEWIDTH3):> fi.lowpass(2,cutoff) * ampEnv;							// WAVESUMMING
  cutoff = (freqEnv + 0.01) * 4000 * freq / 600 * (1 - min(freq,1000)/2000) : limit(20,20000);							// FC
  freqEnv = (1 + (acc - 5.0)/5.0) * en.arfe(0.001,1.6,0.4 * tempo_RelFactor,trigger) : si.smooth(ba.tau2pole(0.0001));	// FREQUENCY ENV
  ampEnv = pow(en.ar(0.001,4 * tempo_RelFactor,trigger),6)  : si.smooth(ba.tau2pole(0.0001));							// AMPLITUDE ENV
};

voiceSynth_FormantBP(freq,vel,trigger,acc) = pm.SFFormantModelBP(2,vowel_H,fric,freqLow,0.04) * env : fi.resonlp(8000,3,1) with
{
  	fric = 0.13 - acc/10.0 * 0.13 : max(0);
	freqLow = freq / 2.0;
  	vowel_idx = 0;
	env = en.ar(0.02, 1.5  / tempo * 78.6 * tempo_RelFactor * (1 + acc/5.0), trigger);
  	vowel_H = vowel_idx : si.smooth(ba.tau2pole(0.01));
};

fullChordSynth(freqList,synthFunc,env) = stereoChordOut with
{ 
  freqSelector(n) = freqList : ba.selectn(4,n-1);																			// INDIVIDUAL FREQS
  strumDelay(dMax) = dMax * (tempo < 120) * (120 - tempo)/60;																// CALCULATE DELAY
  freq1Bus = synthFunc(freqSelector(1)),synthFunc(freqSelector(1) + FREQ_OFFSET_LR);										// F1
  freq2Bus = synthFunc(freqSelector(2)),synthFunc(freqSelector(2) + FREQ_OFFSET_LR) : shortDelay(strumDelay(CS_DEL_N1));	// F2	
  freq3Bus = synthFunc(freqSelector(3)),synthFunc(freqSelector(3) + FREQ_OFFSET_LR) : shortDelay(strumDelay(CS_DEL_N2)); 	// F3
  freq4Bus = synthFunc(freqSelector(4)),synthFunc(freqSelector(4) + FREQ_OFFSET_LR) : shortDelay(strumDelay(CS_DEL_N3)); 	// F4
  stereoChordOut = freq1Bus,freq2Bus,freq3Bus,freq4Bus :> stereoLinGain(env);												// SUM + ENVELOPE
};

chordSingle_Synth(freq,acc,synthFunc) = noteOut with
{
  noteOut = synthFunc(freq,acc),synthFunc(freq + 0.5,acc);
};

ks(freq,damping) = +~((de.fdelay4(1024,del)*damping) : dampingFilter)
  with
{
  del = ma.SR/freqCooked - 0.5 - 1*(freqCooked > 600);																	// CALCULATE DELAY LENGTH + TUNING COMPENSATE
  dampingFilter = _ <: (_'+ _)/2;																						// DAMPING FB FILTER
  freqCooked = freq * 1.0116;
};

ks_excitation(trigger) = no.noise*en.ar(0.001,0.001,trigger);															// KARPLUS STRONG NOISE EXCITATION

staticBalanceMult(z) = 0.5 * (z == 3) + 1.2 * (z == 4) + 1.4 * (z == 5), 0.5 * (z == 3) + 1.2 * (z == 4) + 1.4 * (z == 6) : stereoEffect(si.smoo); 

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // S O N I // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// MASTER FILTER - LPF
Soni_R3_Filter_1 = fi.resonlp(cutoff,qCooked,1) with 																		// R3 - BRIGHTNESS
{
  cutoff = (Soni_R3_1_Fc_Max - X_M_Brightness * (Soni_R3_1_Fc_Max - Soni_R3_1_Fc_Min)), 20000 : select2(X_M_Brightness < 0.001) : si.smoo;
  qCooked = 1;
};

Soni_R3_Filter_2 = fi.resonlp(cutoff,qCooked,1) with 																		// R3 - BRIGHTNESS
{
  cutoff = (Soni_R3_2_Fc_Max - X_M_Brightness * (Soni_R3_2_Fc_Max - Soni_R3_2_Fc_Min)), 20000 : select2(X_M_Brightness < 0.001) : si.smoo;
  qCooked = 4 - 3.3*X_M_Brightness;
};

Soni_SyncMusic(maxDelay) = _,_ : de.fdelay(50000,cookedDelaySamples),de.fdelay(50000,cookedDelaySamples) 
  with 
{
  cookedDelaySamples = maxDelay * X_M_Synchronicity * ma.SR : si.smoo;
// : ba.sAndH(ba.pulse(ma.SR/5));
};

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // Generation // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

// TRIGGERS
TRG_K = velToTrigger(V_K);
TRG_S = velToTrigger(V_S);
TRG_HH = velToTrigger(V_HH);
TRG_C_1 = velToTrigger(V_C_1);
TRG_C_2 = velToTrigger(V_C_2);
TRG_C_3 = velToTrigger(V_C_3);
TRG_C_4 = velToTrigger(V_C_4);
TRG_LIST_C = TRG_C_1,TRG_C_2,TRG_C_3,TRG_C_4;
TRG_R = velToTrigger(V_R);
TRG_M = velToTrigger(V_M);
TRG_CS = velToTrigger(V_CS);
TRG_CR = velToTrigger(V_CR);

//Kick

kick_V1 = samplePlayer(K_SMPL_V1,TRG_K);
kick_V2 = samplePlayer(K_SMPL_V2,TRG_K);
kick_V3 = samplePlayer(K_SMPL_V3,TRG_K);
kickSynth = kick_V1,kick_V2,kick_V3 : ba.selectn(3,VAR_1 - 1);
kick_Normal = kickSynth : applyVelocity(V_K,TRG_K,9); 
kickTrack = kick_Normal,(kickSynth * 1.4) :> monoChannel(1) : getPanFunction(0);

//Snare

snare_V1 = samplePlayer(S_SMPL_V1_1,TRG_S), samplePlayer(S_SMPL_V1_2,TRG_S),samplePlayer(S_SMPL_V1_3,TRG_S) : ba.selectn(3,S_FNUM);
snare_V2 = samplePlayer(S_SMPL_V2_1,TRG_S), samplePlayer(S_SMPL_V2_2,TRG_S),samplePlayer(S_SMPL_V2_3,TRG_S) : ba.selectn(3,S_FNUM);
snare_V3 = samplePlayer(S_SMPL_V3_1,TRG_S), samplePlayer(S_SMPL_V3_2,TRG_S),samplePlayer(S_SMPL_V3_3,TRG_S) : ba.selectn(3,S_FNUM);
snareSynth = snare_V1,snare_V2,snare_V3 : ba.selectn(3,VAR_2 - 1);
snare_Normal = snareSynth : applyVelocity(V_S,TRG_S,3);
snareTrack = snare_Normal,(snareSynth * 1.4) :> monoChannel(2) : getPanFunction(0);																		

//HH

hh_V1 = samplePlayer(HH_SMPL_V1_1,TRG_HH), samplePlayer(HH_SMPL_V1_2,TRG_HH),samplePlayer(HH_SMPL_V1_3,TRG_HH) : ba.selectn(3,HH_FNUM);
hh_V2 = samplePlayer(HH_SMPL_V2_1,TRG_HH), samplePlayer(HH_SMPL_V2_2,TRG_HH),samplePlayer(HH_SMPL_V2_3,TRG_HH) : ba.selectn(3,HH_FNUM);
hh_V3 = pm.marimba(800,0.75,5000,1,1,TRG_HH) * 10;
hhSynth = hh_V1,hh_V2,hh_V3 : ba.selectn(3,VAR_3 - 1);
hhTrack = hhSynth : applyVelocity(V_HH,TRG_HH,3) : monoChannel(3) : getPanFunction(1);	

//Chord

KEYNUM_LIST_C = KEYNUM_C_1,KEYNUM_C_2,KEYNUM_C_3,KEYNUM_C_4;																// LIST MIDI KEYS
F0_LIST_HZ_C = getChordFinalFreqs(KEYNUM_LIST_C);																			// MIDI KEYS TO FREQ
ACC_LIST_C = ACC_C_1,ACC_C_2,ACC_C_3,ACC_C_4;																				// ACCENTS
chordFreq(noteIdx) = F0_LIST_HZ_C : ba.selectn(4,noteIdx);																	// FREQ SELECTOR
chordVel(noteIdx) =  V_LIST_C 	  : ba.selectn(4,noteIdx);																	// VEL SELECTOR
chordTrg(noteIdx) =  TRG_LIST_C	  : ba.selectn(4,noteIdx);																	// TRG SELECTOR
chordAcc(noteIdx) = ACC_LIST_C : ba.selectn(4,noteIdx);																		// ACC SELECTOR
chord_SF_V1(trigger,freq,acc) = pianoSim_singleNote(freq,trigger,acc);														// CHORD - SF VARIANT 1
chord_SF_V2(trigger,freq,acc) = fmSynth_Versatile(freq,MALLET_MRATIO,MALLET_I_FIXED,MALLET_I_ENV,
											  MALLET_A,MALLET_D,MALLET_S,MALLET_R,MALLET_ENVTYPE,trigger,7,acc);			// CHORD - SF VARIANT 2
chord_SF_V3(trigger,freq,acc) 
  = os.CZresTrap(0.5*(1+os.osc(freq)),4.54 * (1 + pow(acc/5,2))) * en.are(0.001,2 * tempo_RelFactor,trigger);
chord_notePanFunc(idx) = ba.take(idx+1,PANPOS_NOTES);
chordSynthFunc(trigger,freq,acc) = chord_SF_V1(trigger,freq,acc), chord_SF_V2(trigger,freq,acc), chord_SF_V3(trigger,freq,acc) : ba.selectn(3,VAR_4 - 1);
chordSum = par(i,4,chordSingle_Synth(chordFreq(i), chordAcc(i), chordSynthFunc(chordTrg(i))) : stereoEffect(applyVelocity(chordVel(i),chordTrg(i),9))) :> _,_;
chordTrack = chordSum : stereoChannel(4);

//Riff

F0_R = KEYNUM_R;																					// CALCULATE F0 HZ
riff_V1 = fmSynth(F0_R,MOD_NUM_R,FREQ_FACTOR_R,RL_R,MOD_DEPTH_R,TRG_R);														// RIFF VARIANT 1
riff_V2 = fmSynth_Versatile(F0_R,BASSLINE_MRATIO,BASSLINE_I_FIXED,BASSLINE_I_ENV,
											  BASSLINE_A,BASSLINE_D,BASSLINE_S,BASSLINE_R,BASSLINE_ENVTYPE,TRG_R,V_R,ACC_R);		// RIFF VARIANT 2
riff_V3 = fmSynth_Versatile(F0_R,AGGRO_MRATIO,AGGRO_I_FIXED,AGGRO_I_ENV,
											  AGGRO_A,AGGRO_D,AGGRO_S,AGGRO_R,AGGRO_ENVTYPE,TRG_R,V_R,ACC_R);						// RIFF VARIANT 2
riffSynth = riff_V1,riff_V2,riff_V3 : ba.selectn(3,VAR_5 - 1);
riffTrack = riffSynth : applyVelocity(V_R,TRG_R,9) : monoChannel(5) : getPanFunction(0);

//Melody Main

F0_M = KEYNUM_M;
V_M_SUS = V_M : ba.sAndH(TRG_M);
M_FreqFactor = (F0_M - 300)/700 : si.smooth(ba.tau2pole(0.001));
M_V1(freq) = voiceSynth_FormantBP(freq,V_M_SUS,TRG_M,ACC_M);																// MELODY SF - VARIANT 1
M_V2(freq) = fmSynth_Versatile(freq,MALLET_MRATIO,MALLET_I_FIXED,MALLET_I_ENV,
											  MALLET_A,MALLET_D,MALLET_S,MALLET_R,MALLET_ENVTYPE,TRG_M,V_M,ACC_M);			// MELODY SF - VARIANT 2
M_V3(freq) = fmSynth_Versatile(freq,TRUMPET_MRATIO,TRUMPET_I_FIXED,TRUMPET_I_ENV,
											  TRUMPET_A,TRUMPET_D,TRUMPET_S,TRUMPET_R,TRUMPET_ENVTYPE,TRG_M,V_M,ACC_M);		// MELODY SF - VARIANT 3
M_SynthFunc(freq) = M_V1(freq),M_V2(freq),M_V3(freq) : ba.selectn(3,VAR_6 - 1);
M_FX1 = dotted_delay(FB_DEL_M,BT_SMPL,WET_DEL_M),dotted_delay(FB_DEL_M,2*BT_SMPL,WET_DEL_M);								// DEFINE STEREO DOTTED DELAY
melodySynth = leadSynth(F0_M,M_SynthFunc,V_M,TRG_M,RL_M,FC_LP_M,ACC_M);														// SYNTHESIZE MELODY
melodyTrack = melodySynth : M_FX1 : stereoChannel(6);

//Chord Stabs

KEYNUM_LIST_CS = KEYNUM_CS_1,KEYNUM_CS_2,KEYNUM_CS_3,KEYNUM_CS_4;
F0_LIST_HZ_CS = getChordFinalFreqs(KEYNUM_LIST_CS);																			// GET F0 LIST
ENV_CS = en.ar(AT_CS,RL_CS,TRG_CS);																							// GET ENV
DEL_CS = stereoEffect(dotted_delay(FB_DEL_CS,BT_SMPL,WET_DEL_CS));															// DEFINE DOTTED DELAY
CS_V1(freq) = ks_excitation(TRG_CS) : ks(freq,DMP_KS_CS);
CS_V2(freq) = os.triangle(freq);
CS_V3(freq) = os.sawtooth(freq);
SynthFunc_CS(freq) = CS_V1(freq),CS_V2(freq),CS_V3(freq) : ba.selectn(3,VAR_7 - 1);
CSTrack = fullChordSynth(F0_LIST_HZ_CS,SynthFunc_CS,ENV_CS) : stereoLinGain(0.3) : DEL_CS;									// CS SYNTH
chordStabTrack = CSTrack : stereoChannel(7);

//Crash

crash_V1 = samplePlayer(CR_SMPL_V1,TRG_CR);
crash_V2 = samplePlayer(CR_SMPL_V2,TRG_CR);
crash_V3 = samplePlayer(CR_SMPL_V3,TRG_CR);
crashSynth = crash_V1,crash_V2,crash_V3 : ba.selectn(3,VAR_8 - 1);
crashTrack = crashSynth : applyVelocity(V_CR,TRG_CR,9) : monoChannel(8) : getPanFunction(2);

// // // // // // // // // // // // // // // // // // // // // // // // // // // // TRADITIONAL STRATEGIES // // // // // // // // // // // // // // // // // // // // // // // // // // // //

S1_Pitch = os.osc(S1_freq) *(0.5);
S1_freq = S1_fmin * pow(2,X_T_Pitch*S1_nOct);
S1_fmin = 300;
S1_nOct = 3.5;

S2_Tempo = os.osc(1000) * en.ar(0.001,0.05,S2_PulseTrain) *(0.5);
S2_PulseTrain = ba.pulse(S2_SampleInterval);
S2_TempoMax = 20*60; 		S2_TempoMin = 2*60;
S2_IntervalRange = ba.tempo(S2_TempoMin) - ba.tempo(S2_TempoMax);
S2_SampleInterval = ba.tempo(S2_TempoMax) + X_T_Tempo * (S2_IntervalRange);

S3_Synchronicity = (S3_OriginalTrain + S3_Delayed) : en.ar(0.001,0.05) : *(os.osc(1000) *(0.5));
S3_PulseFreq = 3;  S3_PeriodSamples = ba.sec2samp(1/S3_PulseFreq);
S3_MaxSampleDelay = 0.25 * S3_PeriodSamples;
S3_CurrentDelay = S3_MaxSampleDelay * X_T_Synchronicity; 
S3_OriginalTrain = ba.pulse(S3_PeriodSamples);
S3_Delayed = S3_OriginalTrain : de.fdelay(40000,S3_CurrentDelay);

S4_Inharmonicity = (os.osc(S4_F) + S4_addedPartials) * 0.1;
S4_addedPartials = par(i,15,S4_InharmExp(i)) :> _;
S4_InharmExp(i) = os.osc(S4_F*i*sqrt(1+ X_T_Harmonicity/10*i*i));
S4_F = 200;

S5_Brightness = no.noise : fi.resonlp(S5_fc,0.7,1);
S5_fc = S5_fmin * pow(2,(1-X_T_Brightness)*S5_nOct);
S5_fmin = 300;
S5_nOct = 3.5;

tradSoniOut = S1_Pitch,S2_Tempo,S3_Synchronicity,S4_Inharmonicity,S5_Brightness : ba.selectn(5,Soni_Choice_Trad) <: _,_;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // M A S T E R // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

track1 = kickTrack		: Soni_SyncMusic(Soni_R1_MaxDelSec(0)) 		: stereoMasterSection(1);
track2 = snareTrack 	: Soni_SyncMusic(Soni_R1_MaxDelSec(1))		: stereoMasterSection(2);
track3 = hhTrack 		: Soni_SyncMusic(Soni_R1_MaxDelSec(2))		: stereoMasterSection(3);
track4 = chordTrack 	: Soni_SyncMusic(Soni_R1_MaxDelSec(3))		: stereoMasterSection(4);
track5 = riffTrack 		: Soni_SyncMusic(Soni_R1_MaxDelSec(4))		: stereoMasterSection(5);
track6 = melodyTrack 	: Soni_SyncMusic(Soni_R1_MaxDelSec(5))		: stereoMasterSection(6);
track7 = chordStabTrack : Soni_SyncMusic(Soni_R1_MaxDelSec(6))		: stereoMasterSection(7);
track8 = crashTrack 	: Soni_SyncMusic(Soni_R1_MaxDelSec(7))		: stereoMasterSection(8);

percBus = track1,track2,track3,track8 :> stereoEffect(Soni_R3_Filter_1);
reverbBus = track2,track3,track4,track6,track7 : par(i,5,stereodBGain(ba.take(i+1,REV_SND))) :> reverbMaster;
melBus = track4,track5,track6,track7,reverbBus :> stereoEffect(Soni_R3_Filter_2);

masterChannel = masterComp : stereoEffect(parametricEQ(masterEQGroup))
  						   : stereoLinGain(masterGain) : stereoEffect(masterLimiter(0)) : stereoEffect(hard_clip(1));
musicBus = melBus,percBus,reverbBus :> masterChannel;

process = musicBus,tradSoniOut : ba.select2stereo(sonificationType);