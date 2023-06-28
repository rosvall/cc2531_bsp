// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>

enum rfc_obs_sig {
	RFC_OBS_SIG0 = 123, // 1111011 (123): rfc_obs_sig0
	RFC_OBS_SIG1 = 124, // 1111100 (124): rfc_obs_sig1
	RFC_OBS_SIG2 = 125, // 1111101 (125): rfc_obs_sig2
};

/* Bit controlling the observation output 0 on P1[0].
0 - Observation output disabled
1 - Observation output enabled
Note: If enabled, this overwrites the standard GPIO behavior of P1.0. 
(Reset=0) (R/W)*/ 
#define OBS_SEL_ENABLE BIT(7)

__xdata __at(0x6243) struct {
	/* 0x6243 ### OBSSEL0..5 (0x6243) - Observation Output Control Register 0 */ 
	uint8_t obssel[6];
} OBS;

#define obs_enable(_pin_num, _signal)  \
	do {                               \
		OBS.obssel[_pin_num] = (_signal) | OBS_SEL_ENABLE; \
	} while (0)

#define obs_disable(_pin_num)   \
	do {                        \
		OBS.obssel[_pin_num] &= ~OBS_SEL_ENABLE;   \
	} while (0)

/*
Potentially interesting values for OBSSELn:

(VALUE includes EN bit, DATA is just some indication of number of edges on output pin over 1/4 second)

128
129
130
131
132
133
134
135 Timer4 interrupt?
136
137
138
139
140
141 Uart tx byte begin spikes
142
143
144
145 radio tx (or rx) byte begin flag 
146
147
148
149
150
151
152
153
154
155
156
157
158 edges:1507	Related to 197 RF PLL
159 edges:1304	Related to 197 RF PLL
160 edges:984	Related to 197 RF PLL
161
162
163
164
165
166 edges:387	Spikes at start of uart TX bytes
167 edges:157	Multiple spikes around groups of packets. Interrupt flag? Probably USB interrupt
168 edges:88		Single spike at start and end of packets. Interrupt flag?
169
170
171
172
173 edges:111	Multiple spikes around groups of packets. Interrupt flag? Maybe DMA done intr
174
175 Timer4 interrupt?
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197 edges:1403	related to RF PLL: 20us of 6.4MHz clock when PLL_LOCK goes low; bursts before that
198 edges:30559	related to 197 RF PLL
199
200
201
202
203 edges:30444	something fast
204 edges:31067	something fast
205 edges:32764	something fast
206 edges:30674	something fast
207 edges:29916	something fast
208 edges:32229	something fast
209 edges:33915	something fast
210 edges:34256	something fast
211 edges:32531	32MHz data very bursty. correlated with slightly before radio rx data and 20ms after
212 edges:29698	32MHz data very bursty. correlated with slightly before radio rx data and 20ms after
213 edges:34280	32MHz data bursty. correlated with slightly before radio rx data and 20ms after
214 edges:30195	32MHz data bursty. correlated with slightly before radio rx data and 20ms after
215 edges:27977	32MHz data bursty. correlated with slightly before radio rx data and 20ms after
216 edges:29322	32MHz data bursty. correlated with slightly before radio rx data and 20ms after
217 edges:28169	32MHz data bursty. somewhat correlated with radio rx data
218 edges:31293	32MHz data
219 edges:29674	32MHz data
220 edges:26191	32MHz data
221 edges:23348	32MHz data
222 edges:18852	32MHz data
223 edges:14587	32MHz data
224 edges:10537	32MHz data
225 edges:8781	Fast data or clock, slightly correlated with radio rx data but not really
226 edges:4839	Fast data or clock, slightly correlated with radio rx data but not really
227 edges:4139	Fast data or clock, slightly correlated with radio rx data but not really
228 edges:4008	Fast data or clock, slightly correlated with radio rx data but not really
229 edges:4463	Fast data or clock, slightly correlated with radio rx data but not really
230 edges:1811	Fast data or clock, slightly correlated with radio rx data but not really
231 edges:3018	Fast data or clock, slightly correlated with radio rx data but not really
232 edges:1643	Fast data or status flag, slightly correlated with radio rx data but not really
233
234 edges:975	Narrow spikes (more bursts). Correlated with interrupt activity.
235 edges:32946	Something fast
236 edges:911	Narrow spikes (few very short bursts)
237 edges:32806	Something fast
238
239
240
241
242
243
244
245 edges:30116	Something VERY fast
246
247
248 48MHz clock
249 12MHz clock
250 32MHz clock
251 RFC_OBS_SIG0
252 RFC_OBS_SIG1
253 RFC_OBS_SIG2
254
255

*/
