
./myled.elf:     file format elf32-littlearm


Disassembly of section ER_IROM1:

08000000 <__Vectors>:
 8000000:	08 04 00 20 ed 00 00 08 f5 00 00 08 f7 00 00 08     ... ............
 8000010:	f9 00 00 08 fb 00 00 08 fd 00 00 08 00 00 00 00     ................
	...
 800002c:	ff 00 00 08 01 01 00 08 00 00 00 00 03 01 00 08     ................
 800003c:	05 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800004c:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800005c:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800006c:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800007c:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800008c:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 800009c:	07 01 00 08 07 01 00 08 07 01 00 08 00 00 00 00     ................
 80000ac:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 80000bc:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 80000cc:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................
 80000dc:	07 01 00 08 07 01 00 08 07 01 00 08 07 01 00 08     ................

080000ec <Reset_Handler>:
 80000ec:	4809      	ldr	r0, [pc, #36]	@ (8000114 <__user_initial_stackheap+0xc>)
 80000ee:	4780      	blx	r0
 80000f0:	4809      	ldr	r0, [pc, #36]	@ (8000118 <__user_initial_stackheap+0x10>)
 80000f2:	4700      	bx	r0

080000f4 <NMI_Handler>:
 80000f4:	e7fe      	b.n	80000f4 <NMI_Handler>

080000f6 <HardFault_Handler>:
 80000f6:	e7fe      	b.n	80000f6 <HardFault_Handler>

080000f8 <MemManage_Handler>:
 80000f8:	e7fe      	b.n	80000f8 <MemManage_Handler>

080000fa <BusFault_Handler>:
 80000fa:	e7fe      	b.n	80000fa <BusFault_Handler>

080000fc <UsageFault_Handler>:
 80000fc:	e7fe      	b.n	80000fc <UsageFault_Handler>

080000fe <SVC_Handler>:
 80000fe:	e7fe      	b.n	80000fe <SVC_Handler>

08000100 <DebugMon_Handler>:
 8000100:	e7fe      	b.n	8000100 <DebugMon_Handler>

08000102 <PendSV_Handler>:
 8000102:	e7fe      	b.n	8000102 <PendSV_Handler>

08000104 <SysTick_Handler>:
 8000104:	e7fe      	b.n	8000104 <SysTick_Handler>

08000106 <ADC1_2_IRQHandler>:
 8000106:	e7fe      	b.n	8000106 <ADC1_2_IRQHandler>

08000108 <__user_initial_stackheap>:
 8000108:	4804      	ldr	r0, [pc, #16]	@ (800011c <__user_initial_stackheap+0x14>)
 800010a:	4905      	ldr	r1, [pc, #20]	@ (8000120 <__user_initial_stackheap+0x18>)
 800010c:	4a05      	ldr	r2, [pc, #20]	@ (8000124 <__user_initial_stackheap+0x1c>)
 800010e:	4b06      	ldr	r3, [pc, #24]	@ (8000128 <__user_initial_stackheap+0x20>)
 8000110:	4770      	bx	lr
 8000112:	0000      	.short	0x0000
 8000114:	080001a1 	.word	0x080001a1
 8000118:	0800012d 	.word	0x0800012d
 800011c:	20000408 	.word	0x20000408
 8000120:	20000408 	.word	0x20000408
 8000124:	20000608 	.word	0x20000608
 8000128:	20000008 	.word	0x20000008

0800012c <main>:
 800012c:	b480      	push	{r7}
 800012e:	b083      	sub	sp, #12
 8000130:	af00      	add	r7, sp, #0
 8000132:	4b18      	ldr	r3, [pc, #96]	@ (8000194 <main+0x68>)
 8000134:	699b      	ldr	r3, [r3, #24]
 8000136:	4a17      	ldr	r2, [pc, #92]	@ (8000194 <main+0x68>)
 8000138:	f043 0310 	orr.w	r3, r3, #16
 800013c:	6193      	str	r3, [r2, #24]
 800013e:	4b16      	ldr	r3, [pc, #88]	@ (8000198 <main+0x6c>)
 8000140:	685b      	ldr	r3, [r3, #4]
 8000142:	4a15      	ldr	r2, [pc, #84]	@ (8000198 <main+0x6c>)
 8000144:	f443 1340 	orr.w	r3, r3, #3145728	@ 0x300000
 8000148:	6053      	str	r3, [r2, #4]
 800014a:	2301      	movs	r3, #1
 800014c:	607b      	str	r3, [r7, #4]
 800014e:	687b      	ldr	r3, [r7, #4]
 8000150:	2b00      	cmp	r3, #0
 8000152:	d006      	beq.n	8000162 <main+0x36>
 8000154:	4b10      	ldr	r3, [pc, #64]	@ (8000198 <main+0x6c>)
 8000156:	68db      	ldr	r3, [r3, #12]
 8000158:	4a0f      	ldr	r2, [pc, #60]	@ (8000198 <main+0x6c>)
 800015a:	f423 5300 	bic.w	r3, r3, #8192	@ 0x2000
 800015e:	60d3      	str	r3, [r2, #12]
 8000160:	e005      	b.n	800016e <main+0x42>
 8000162:	4b0d      	ldr	r3, [pc, #52]	@ (8000198 <main+0x6c>)
 8000164:	68db      	ldr	r3, [r3, #12]
 8000166:	4a0c      	ldr	r2, [pc, #48]	@ (8000198 <main+0x6c>)
 8000168:	f443 5300 	orr.w	r3, r3, #8192	@ 0x2000
 800016c:	60d3      	str	r3, [r2, #12]
 800016e:	687b      	ldr	r3, [r7, #4]
 8000170:	2b00      	cmp	r3, #0
 8000172:	bf0c      	ite	eq
 8000174:	2301      	moveq	r3, #1
 8000176:	2300      	movne	r3, #0
 8000178:	b2db      	uxtb	r3, r3
 800017a:	607b      	str	r3, [r7, #4]
 800017c:	2300      	movs	r3, #0
 800017e:	603b      	str	r3, [r7, #0]
 8000180:	e002      	b.n	8000188 <main+0x5c>
 8000182:	683b      	ldr	r3, [r7, #0]
 8000184:	3301      	adds	r3, #1
 8000186:	603b      	str	r3, [r7, #0]
 8000188:	683b      	ldr	r3, [r7, #0]
 800018a:	4a04      	ldr	r2, [pc, #16]	@ (800019c <main+0x70>)
 800018c:	4293      	cmp	r3, r2
 800018e:	ddf8      	ble.n	8000182 <main+0x56>
 8000190:	e7dd      	b.n	800014e <main+0x22>
 8000192:	bf00      	nop
 8000194:	40021000 	.word	0x40021000
 8000198:	40011000 	.word	0x40011000
 800019c:	003d08ff 	.word	0x003d08ff

080001a0 <SystemInit>:
 80001a0:	b580      	push	{r7, lr}
 80001a2:	af00      	add	r7, sp, #0
 80001a4:	4b15      	ldr	r3, [pc, #84]	@ (80001fc <SystemInit+0x5c>)
 80001a6:	681b      	ldr	r3, [r3, #0]
 80001a8:	4a14      	ldr	r2, [pc, #80]	@ (80001fc <SystemInit+0x5c>)
 80001aa:	f043 0301 	orr.w	r3, r3, #1
 80001ae:	6013      	str	r3, [r2, #0]
 80001b0:	4b12      	ldr	r3, [pc, #72]	@ (80001fc <SystemInit+0x5c>)
 80001b2:	685a      	ldr	r2, [r3, #4]
 80001b4:	4911      	ldr	r1, [pc, #68]	@ (80001fc <SystemInit+0x5c>)
 80001b6:	4b12      	ldr	r3, [pc, #72]	@ (8000200 <SystemInit+0x60>)
 80001b8:	4013      	ands	r3, r2
 80001ba:	604b      	str	r3, [r1, #4]
 80001bc:	4b0f      	ldr	r3, [pc, #60]	@ (80001fc <SystemInit+0x5c>)
 80001be:	681b      	ldr	r3, [r3, #0]
 80001c0:	4a0e      	ldr	r2, [pc, #56]	@ (80001fc <SystemInit+0x5c>)
 80001c2:	f023 7384 	bic.w	r3, r3, #17301504	@ 0x1080000
 80001c6:	f423 3380 	bic.w	r3, r3, #65536	@ 0x10000
 80001ca:	6013      	str	r3, [r2, #0]
 80001cc:	4b0b      	ldr	r3, [pc, #44]	@ (80001fc <SystemInit+0x5c>)
 80001ce:	681b      	ldr	r3, [r3, #0]
 80001d0:	4a0a      	ldr	r2, [pc, #40]	@ (80001fc <SystemInit+0x5c>)
 80001d2:	f423 2380 	bic.w	r3, r3, #262144	@ 0x40000
 80001d6:	6013      	str	r3, [r2, #0]
 80001d8:	4b08      	ldr	r3, [pc, #32]	@ (80001fc <SystemInit+0x5c>)
 80001da:	685b      	ldr	r3, [r3, #4]
 80001dc:	4a07      	ldr	r2, [pc, #28]	@ (80001fc <SystemInit+0x5c>)
 80001de:	f423 03fe 	bic.w	r3, r3, #8323072	@ 0x7f0000
 80001e2:	6053      	str	r3, [r2, #4]
 80001e4:	4b05      	ldr	r3, [pc, #20]	@ (80001fc <SystemInit+0x5c>)
 80001e6:	f44f 021f 	mov.w	r2, #10420224	@ 0x9f0000
 80001ea:	609a      	str	r2, [r3, #8]
 80001ec:	f000 f87e 	bl	80002ec <SetSysClock>
 80001f0:	4b04      	ldr	r3, [pc, #16]	@ (8000204 <SystemInit+0x64>)
 80001f2:	f04f 6200 	mov.w	r2, #134217728	@ 0x8000000
 80001f6:	609a      	str	r2, [r3, #8]
 80001f8:	bf00      	nop
 80001fa:	bd80      	pop	{r7, pc}
 80001fc:	40021000 	.word	0x40021000
 8000200:	f8ff0000 	.word	0xf8ff0000
 8000204:	e000ed00 	.word	0xe000ed00

08000208 <SystemCoreClockUpdate>:
 8000208:	b480      	push	{r7}
 800020a:	b085      	sub	sp, #20
 800020c:	af00      	add	r7, sp, #0
 800020e:	2300      	movs	r3, #0
 8000210:	60fb      	str	r3, [r7, #12]
 8000212:	2300      	movs	r3, #0
 8000214:	60bb      	str	r3, [r7, #8]
 8000216:	2300      	movs	r3, #0
 8000218:	607b      	str	r3, [r7, #4]
 800021a:	4b2f      	ldr	r3, [pc, #188]	@ (80002d8 <SystemCoreClockUpdate+0xd0>)
 800021c:	685b      	ldr	r3, [r3, #4]
 800021e:	f003 030c 	and.w	r3, r3, #12
 8000222:	60fb      	str	r3, [r7, #12]
 8000224:	68fb      	ldr	r3, [r7, #12]
 8000226:	2b08      	cmp	r3, #8
 8000228:	d011      	beq.n	800024e <SystemCoreClockUpdate+0x46>
 800022a:	68fb      	ldr	r3, [r7, #12]
 800022c:	2b08      	cmp	r3, #8
 800022e:	d83a      	bhi.n	80002a6 <SystemCoreClockUpdate+0x9e>
 8000230:	68fb      	ldr	r3, [r7, #12]
 8000232:	2b00      	cmp	r3, #0
 8000234:	d003      	beq.n	800023e <SystemCoreClockUpdate+0x36>
 8000236:	68fb      	ldr	r3, [r7, #12]
 8000238:	2b04      	cmp	r3, #4
 800023a:	d004      	beq.n	8000246 <SystemCoreClockUpdate+0x3e>
 800023c:	e033      	b.n	80002a6 <SystemCoreClockUpdate+0x9e>
 800023e:	4b27      	ldr	r3, [pc, #156]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 8000240:	4a27      	ldr	r2, [pc, #156]	@ (80002e0 <SystemCoreClockUpdate+0xd8>)
 8000242:	601a      	str	r2, [r3, #0]
 8000244:	e033      	b.n	80002ae <SystemCoreClockUpdate+0xa6>
 8000246:	4b25      	ldr	r3, [pc, #148]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 8000248:	4a25      	ldr	r2, [pc, #148]	@ (80002e0 <SystemCoreClockUpdate+0xd8>)
 800024a:	601a      	str	r2, [r3, #0]
 800024c:	e02f      	b.n	80002ae <SystemCoreClockUpdate+0xa6>
 800024e:	4b22      	ldr	r3, [pc, #136]	@ (80002d8 <SystemCoreClockUpdate+0xd0>)
 8000250:	685b      	ldr	r3, [r3, #4]
 8000252:	f403 1370 	and.w	r3, r3, #3932160	@ 0x3c0000
 8000256:	60bb      	str	r3, [r7, #8]
 8000258:	4b1f      	ldr	r3, [pc, #124]	@ (80002d8 <SystemCoreClockUpdate+0xd0>)
 800025a:	685b      	ldr	r3, [r3, #4]
 800025c:	f403 3380 	and.w	r3, r3, #65536	@ 0x10000
 8000260:	607b      	str	r3, [r7, #4]
 8000262:	68bb      	ldr	r3, [r7, #8]
 8000264:	0c9b      	lsrs	r3, r3, #18
 8000266:	3302      	adds	r3, #2
 8000268:	60bb      	str	r3, [r7, #8]
 800026a:	687b      	ldr	r3, [r7, #4]
 800026c:	2b00      	cmp	r3, #0
 800026e:	d106      	bne.n	800027e <SystemCoreClockUpdate+0x76>
 8000270:	68bb      	ldr	r3, [r7, #8]
 8000272:	4a1c      	ldr	r2, [pc, #112]	@ (80002e4 <SystemCoreClockUpdate+0xdc>)
 8000274:	fb02 f303 	mul.w	r3, r2, r3
 8000278:	4a18      	ldr	r2, [pc, #96]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 800027a:	6013      	str	r3, [r2, #0]
 800027c:	e017      	b.n	80002ae <SystemCoreClockUpdate+0xa6>
 800027e:	4b16      	ldr	r3, [pc, #88]	@ (80002d8 <SystemCoreClockUpdate+0xd0>)
 8000280:	685b      	ldr	r3, [r3, #4]
 8000282:	f403 3300 	and.w	r3, r3, #131072	@ 0x20000
 8000286:	2b00      	cmp	r3, #0
 8000288:	d006      	beq.n	8000298 <SystemCoreClockUpdate+0x90>
 800028a:	68bb      	ldr	r3, [r7, #8]
 800028c:	4a15      	ldr	r2, [pc, #84]	@ (80002e4 <SystemCoreClockUpdate+0xdc>)
 800028e:	fb02 f303 	mul.w	r3, r2, r3
 8000292:	4a12      	ldr	r2, [pc, #72]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 8000294:	6013      	str	r3, [r2, #0]
 8000296:	e00a      	b.n	80002ae <SystemCoreClockUpdate+0xa6>
 8000298:	68bb      	ldr	r3, [r7, #8]
 800029a:	4a11      	ldr	r2, [pc, #68]	@ (80002e0 <SystemCoreClockUpdate+0xd8>)
 800029c:	fb02 f303 	mul.w	r3, r2, r3
 80002a0:	4a0e      	ldr	r2, [pc, #56]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 80002a2:	6013      	str	r3, [r2, #0]
 80002a4:	e003      	b.n	80002ae <SystemCoreClockUpdate+0xa6>
 80002a6:	4b0d      	ldr	r3, [pc, #52]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 80002a8:	4a0d      	ldr	r2, [pc, #52]	@ (80002e0 <SystemCoreClockUpdate+0xd8>)
 80002aa:	601a      	str	r2, [r3, #0]
 80002ac:	bf00      	nop
 80002ae:	4b0a      	ldr	r3, [pc, #40]	@ (80002d8 <SystemCoreClockUpdate+0xd0>)
 80002b0:	685b      	ldr	r3, [r3, #4]
 80002b2:	091b      	lsrs	r3, r3, #4
 80002b4:	f003 030f 	and.w	r3, r3, #15
 80002b8:	4a0b      	ldr	r2, [pc, #44]	@ (80002e8 <SystemCoreClockUpdate+0xe0>)
 80002ba:	5cd3      	ldrb	r3, [r2, r3]
 80002bc:	b2db      	uxtb	r3, r3
 80002be:	60fb      	str	r3, [r7, #12]
 80002c0:	4b06      	ldr	r3, [pc, #24]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 80002c2:	681a      	ldr	r2, [r3, #0]
 80002c4:	68fb      	ldr	r3, [r7, #12]
 80002c6:	fa22 f303 	lsr.w	r3, r2, r3
 80002ca:	4a04      	ldr	r2, [pc, #16]	@ (80002dc <SystemCoreClockUpdate+0xd4>)
 80002cc:	6013      	str	r3, [r2, #0]
 80002ce:	bf00      	nop
 80002d0:	3714      	adds	r7, #20
 80002d2:	46bd      	mov	sp, r7
 80002d4:	bc80      	pop	{r7}
 80002d6:	4770      	bx	lr
 80002d8:	40021000 	.word	0x40021000
 80002dc:	20000000 	.word	0x20000000
 80002e0:	007a1200 	.word	0x007a1200
 80002e4:	003d0900 	.word	0x003d0900
 80002e8:	080003f8 	.word	0x080003f8

080002ec <SetSysClock>:
 80002ec:	b580      	push	{r7, lr}
 80002ee:	af00      	add	r7, sp, #0
 80002f0:	f000 f802 	bl	80002f8 <SetSysClockTo72>
 80002f4:	bf00      	nop
 80002f6:	bd80      	pop	{r7, pc}

080002f8 <SetSysClockTo72>:
 80002f8:	b480      	push	{r7}
 80002fa:	b083      	sub	sp, #12
 80002fc:	af00      	add	r7, sp, #0
 80002fe:	2300      	movs	r3, #0
 8000300:	607b      	str	r3, [r7, #4]
 8000302:	2300      	movs	r3, #0
 8000304:	603b      	str	r3, [r7, #0]
 8000306:	4b3a      	ldr	r3, [pc, #232]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000308:	681b      	ldr	r3, [r3, #0]
 800030a:	4a39      	ldr	r2, [pc, #228]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800030c:	f443 3380 	orr.w	r3, r3, #65536	@ 0x10000
 8000310:	6013      	str	r3, [r2, #0]
 8000312:	4b37      	ldr	r3, [pc, #220]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000314:	681b      	ldr	r3, [r3, #0]
 8000316:	f403 3300 	and.w	r3, r3, #131072	@ 0x20000
 800031a:	603b      	str	r3, [r7, #0]
 800031c:	687b      	ldr	r3, [r7, #4]
 800031e:	3301      	adds	r3, #1
 8000320:	607b      	str	r3, [r7, #4]
 8000322:	683b      	ldr	r3, [r7, #0]
 8000324:	2b00      	cmp	r3, #0
 8000326:	d103      	bne.n	8000330 <SetSysClockTo72+0x38>
 8000328:	687b      	ldr	r3, [r7, #4]
 800032a:	f5b3 6fa0 	cmp.w	r3, #1280	@ 0x500
 800032e:	d1f0      	bne.n	8000312 <SetSysClockTo72+0x1a>
 8000330:	4b2f      	ldr	r3, [pc, #188]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000332:	681b      	ldr	r3, [r3, #0]
 8000334:	f403 3300 	and.w	r3, r3, #131072	@ 0x20000
 8000338:	2b00      	cmp	r3, #0
 800033a:	d002      	beq.n	8000342 <SetSysClockTo72+0x4a>
 800033c:	2301      	movs	r3, #1
 800033e:	603b      	str	r3, [r7, #0]
 8000340:	e001      	b.n	8000346 <SetSysClockTo72+0x4e>
 8000342:	2300      	movs	r3, #0
 8000344:	603b      	str	r3, [r7, #0]
 8000346:	683b      	ldr	r3, [r7, #0]
 8000348:	2b01      	cmp	r3, #1
 800034a:	d14b      	bne.n	80003e4 <SetSysClockTo72+0xec>
 800034c:	4b29      	ldr	r3, [pc, #164]	@ (80003f4 <SetSysClockTo72+0xfc>)
 800034e:	681b      	ldr	r3, [r3, #0]
 8000350:	4a28      	ldr	r2, [pc, #160]	@ (80003f4 <SetSysClockTo72+0xfc>)
 8000352:	f043 0310 	orr.w	r3, r3, #16
 8000356:	6013      	str	r3, [r2, #0]
 8000358:	4b26      	ldr	r3, [pc, #152]	@ (80003f4 <SetSysClockTo72+0xfc>)
 800035a:	681b      	ldr	r3, [r3, #0]
 800035c:	4a25      	ldr	r2, [pc, #148]	@ (80003f4 <SetSysClockTo72+0xfc>)
 800035e:	f023 0303 	bic.w	r3, r3, #3
 8000362:	6013      	str	r3, [r2, #0]
 8000364:	4b23      	ldr	r3, [pc, #140]	@ (80003f4 <SetSysClockTo72+0xfc>)
 8000366:	681b      	ldr	r3, [r3, #0]
 8000368:	4a22      	ldr	r2, [pc, #136]	@ (80003f4 <SetSysClockTo72+0xfc>)
 800036a:	f043 0302 	orr.w	r3, r3, #2
 800036e:	6013      	str	r3, [r2, #0]
 8000370:	4b1f      	ldr	r3, [pc, #124]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000372:	4a1f      	ldr	r2, [pc, #124]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000374:	685b      	ldr	r3, [r3, #4]
 8000376:	6053      	str	r3, [r2, #4]
 8000378:	4b1d      	ldr	r3, [pc, #116]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800037a:	4a1d      	ldr	r2, [pc, #116]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800037c:	685b      	ldr	r3, [r3, #4]
 800037e:	6053      	str	r3, [r2, #4]
 8000380:	4b1b      	ldr	r3, [pc, #108]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000382:	685b      	ldr	r3, [r3, #4]
 8000384:	4a1a      	ldr	r2, [pc, #104]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000386:	f443 6380 	orr.w	r3, r3, #1024	@ 0x400
 800038a:	6053      	str	r3, [r2, #4]
 800038c:	4b18      	ldr	r3, [pc, #96]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800038e:	685b      	ldr	r3, [r3, #4]
 8000390:	4a17      	ldr	r2, [pc, #92]	@ (80003f0 <SetSysClockTo72+0xf8>)
 8000392:	f423 137c 	bic.w	r3, r3, #4128768	@ 0x3f0000
 8000396:	6053      	str	r3, [r2, #4]
 8000398:	4b15      	ldr	r3, [pc, #84]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800039a:	685b      	ldr	r3, [r3, #4]
 800039c:	4a14      	ldr	r2, [pc, #80]	@ (80003f0 <SetSysClockTo72+0xf8>)
 800039e:	f443 13e8 	orr.w	r3, r3, #1900544	@ 0x1d0000
 80003a2:	6053      	str	r3, [r2, #4]
 80003a4:	4b12      	ldr	r3, [pc, #72]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003a6:	681b      	ldr	r3, [r3, #0]
 80003a8:	4a11      	ldr	r2, [pc, #68]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003aa:	f043 7380 	orr.w	r3, r3, #16777216	@ 0x1000000
 80003ae:	6013      	str	r3, [r2, #0]
 80003b0:	bf00      	nop
 80003b2:	4b0f      	ldr	r3, [pc, #60]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003b4:	681b      	ldr	r3, [r3, #0]
 80003b6:	f003 7300 	and.w	r3, r3, #33554432	@ 0x2000000
 80003ba:	2b00      	cmp	r3, #0
 80003bc:	d0f9      	beq.n	80003b2 <SetSysClockTo72+0xba>
 80003be:	4b0c      	ldr	r3, [pc, #48]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003c0:	685b      	ldr	r3, [r3, #4]
 80003c2:	4a0b      	ldr	r2, [pc, #44]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003c4:	f023 0303 	bic.w	r3, r3, #3
 80003c8:	6053      	str	r3, [r2, #4]
 80003ca:	4b09      	ldr	r3, [pc, #36]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003cc:	685b      	ldr	r3, [r3, #4]
 80003ce:	4a08      	ldr	r2, [pc, #32]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003d0:	f043 0302 	orr.w	r3, r3, #2
 80003d4:	6053      	str	r3, [r2, #4]
 80003d6:	bf00      	nop
 80003d8:	4b05      	ldr	r3, [pc, #20]	@ (80003f0 <SetSysClockTo72+0xf8>)
 80003da:	685b      	ldr	r3, [r3, #4]
 80003dc:	f003 030c 	and.w	r3, r3, #12
 80003e0:	2b08      	cmp	r3, #8
 80003e2:	d1f9      	bne.n	80003d8 <SetSysClockTo72+0xe0>
 80003e4:	bf00      	nop
 80003e6:	370c      	adds	r7, #12
 80003e8:	46bd      	mov	sp, r7
 80003ea:	bc80      	pop	{r7}
 80003ec:	4770      	bx	lr
 80003ee:	bf00      	nop
 80003f0:	40021000 	.word	0x40021000
 80003f4:	40022000 	.word	0x40022000

080003f8 <AHBPrescTable>:
	...
 8000400:	04030201 09080706                       ........
