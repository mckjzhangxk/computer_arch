
led.axf:     file format elf32-littlearm


Disassembly of section ER_IROM1:

08000000 <__Vectors>:
 8000000:	60 06 00 20 6d 01 00 08 75 01 00 08 77 01 00 08     `.. m...u...w...
 8000010:	79 01 00 08 7b 01 00 08 7d 01 00 08 00 00 00 00     y...{...}.......
	...
 800002c:	7f 01 00 08 81 01 00 08 00 00 00 00 83 01 00 08     ................
 800003c:	85 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800004c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800005c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800006c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800007c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800008c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 800009c:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 80000ac:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 80000bc:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 80000cc:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................
 80000dc:	87 01 00 08 87 01 00 08 87 01 00 08 87 01 00 08     ................

080000ec <__main>:
 80000ec:	f000 f802 	bl	80000f4 <__scatterload_rt2>
 80000f0:	f000 f82c 	bl	800014c <__rt_entry>

080000f4 <__scatterload_rt2>:
 80000f4:	a00a      	add	r0, pc, #40	@ (adr r0, 8000120 <__scatterload_null+0x1e>)
 80000f6:	e890 0c00 	ldmia.w	r0, {sl, fp}
 80000fa:	4482      	add	sl, r0
 80000fc:	4483      	add	fp, r0
 80000fe:	f1aa 0701 	sub.w	r7, sl, #1

08000102 <__scatterload_null>:
 8000102:	45da      	cmp	sl, fp
 8000104:	d101      	bne.n	800010a <__scatterload_null+0x8>
 8000106:	f000 f821 	bl	800014c <__rt_entry>
 800010a:	f2af 0e09 	subw	lr, pc, #9
 800010e:	e8ba 000f 	ldmia.w	sl!, {r0, r1, r2, r3}
 8000112:	f013 0f01 	tst.w	r3, #1
 8000116:	bf18      	it	ne
 8000118:	1afb      	subne	r3, r7, r3
 800011a:	f043 0301 	orr.w	r3, r3, #1
 800011e:	4718      	bx	r3
 8000120:	0000026c 	.word	0x0000026c
 8000124:	0000027c 	.word	0x0000027c

08000128 <__scatterload_zeroinit>:
 8000128:	2300      	movs	r3, #0
 800012a:	2400      	movs	r4, #0
 800012c:	2500      	movs	r5, #0
 800012e:	2600      	movs	r6, #0
 8000130:	3a10      	subs	r2, #16
 8000132:	bf28      	it	cs
 8000134:	c178      	stmiacs	r1!, {r3, r4, r5, r6}
 8000136:	d8fb      	bhi.n	8000130 <__scatterload_zeroinit+0x8>
 8000138:	0752      	lsls	r2, r2, #29
 800013a:	bf28      	it	cs
 800013c:	c130      	stmiacs	r1!, {r4, r5}
 800013e:	bf48      	it	mi
 8000140:	600b      	strmi	r3, [r1, #0]
 8000142:	4770      	bx	lr

08000144 <__rt_lib_init>:
 8000144:	b51f      	push	{r0, r1, r2, r3, r4, lr}

08000146 <__rt_lib_init_alloca_1>:
 8000146:	bd1f      	pop	{r0, r1, r2, r3, r4, pc}

08000148 <__rt_lib_shutdown>:
 8000148:	b510      	push	{r4, lr}

0800014a <__rt_lib_shutdown_cpp_1>:
 800014a:	bd10      	pop	{r4, pc}

0800014c <__rt_entry>:
 800014c:	f000 f831 	bl	80001b2 <__user_setup_stackheap>
 8000150:	4611      	mov	r1, r2

08000152 <__rt_entry_li>:
 8000152:	f7ff fff7 	bl	8000144 <__rt_lib_init>

08000156 <__rt_entry_main>:
 8000156:	f000 f90b 	bl	8000370 <main>
 800015a:	f000 f84f 	bl	80001fc <exit>

0800015e <__rt_exit>:
 800015e:	b403      	push	{r0, r1}

08000160 <__rt_exit_ls>:
 8000160:	f7ff fff2 	bl	8000148 <__rt_lib_shutdown>

08000164 <__rt_exit_exit>:
 8000164:	bc03      	pop	{r0, r1}
 8000166:	f000 f857 	bl	8000218 <_sys_exit>
	...

0800016c <Reset_Handler>:
 800016c:	4809      	ldr	r0, [pc, #36]	@ (8000194 <__user_initial_stackheap+0xc>)
 800016e:	4780      	blx	r0
 8000170:	4809      	ldr	r0, [pc, #36]	@ (8000198 <__user_initial_stackheap+0x10>)
 8000172:	4700      	bx	r0

08000174 <NMI_Handler>:
 8000174:	e7fe      	b.n	8000174 <NMI_Handler>

08000176 <HardFault_Handler>:
 8000176:	e7fe      	b.n	8000176 <HardFault_Handler>

08000178 <MemManage_Handler>:
 8000178:	e7fe      	b.n	8000178 <MemManage_Handler>

0800017a <BusFault_Handler>:
 800017a:	e7fe      	b.n	800017a <BusFault_Handler>

0800017c <UsageFault_Handler>:
 800017c:	e7fe      	b.n	800017c <UsageFault_Handler>

0800017e <SVC_Handler>:
 800017e:	e7fe      	b.n	800017e <SVC_Handler>

08000180 <DebugMon_Handler>:
 8000180:	e7fe      	b.n	8000180 <DebugMon_Handler>

08000182 <PendSV_Handler>:
 8000182:	e7fe      	b.n	8000182 <PendSV_Handler>

08000184 <SysTick_Handler>:
 8000184:	e7fe      	b.n	8000184 <SysTick_Handler>

08000186 <ADC1_2_IRQHandler>:
 8000186:	e7fe      	b.n	8000186 <ADC1_2_IRQHandler>

08000188 <__user_initial_stackheap>:
 8000188:	4804      	ldr	r0, [pc, #16]	@ (800019c <__user_initial_stackheap+0x14>)
 800018a:	4905      	ldr	r1, [pc, #20]	@ (80001a0 <__user_initial_stackheap+0x18>)
 800018c:	4a05      	ldr	r2, [pc, #20]	@ (80001a4 <__user_initial_stackheap+0x1c>)
 800018e:	4b06      	ldr	r3, [pc, #24]	@ (80001a8 <__user_initial_stackheap+0x20>)
 8000190:	4770      	bx	lr
 8000192:	0000      	.short	0x0000
 8000194:	08000311 	.word	0x08000311
 8000198:	080000ed 	.word	0x080000ed
 800019c:	20000060 	.word	0x20000060
 80001a0:	20000660 	.word	0x20000660
 80001a4:	20000260 	.word	0x20000260
 80001a8:	20000260 	.word	0x20000260

080001ac <__use_two_region_memory>:
 80001ac:	4770      	bx	lr

080001ae <__rt_heap_escrow$2region>:
 80001ae:	4770      	bx	lr

080001b0 <__rt_heap_expand$2region>:
 80001b0:	4770      	bx	lr

080001b2 <__user_setup_stackheap>:
 80001b2:	4675      	mov	r5, lr
 80001b4:	f000 f82c 	bl	8000210 <__user_libspace>
 80001b8:	46ae      	mov	lr, r5
 80001ba:	0005      	movs	r5, r0
 80001bc:	4669      	mov	r1, sp
 80001be:	4653      	mov	r3, sl
 80001c0:	f020 0007 	bic.w	r0, r0, #7
 80001c4:	4685      	mov	sp, r0
 80001c6:	b018      	add	sp, #96	@ 0x60
 80001c8:	b520      	push	{r5, lr}
 80001ca:	f7ff ffdd 	bl	8000188 <__user_initial_stackheap>
 80001ce:	e8bd 4020 	ldmia.w	sp!, {r5, lr}
 80001d2:	f04f 0600 	mov.w	r6, #0
 80001d6:	f04f 0700 	mov.w	r7, #0
 80001da:	f04f 0800 	mov.w	r8, #0
 80001de:	f04f 0b00 	mov.w	fp, #0
 80001e2:	f021 0107 	bic.w	r1, r1, #7
 80001e6:	46ac      	mov	ip, r5
 80001e8:	e8ac 09c0 	stmia.w	ip!, {r6, r7, r8, fp}
 80001ec:	e8ac 09c0 	stmia.w	ip!, {r6, r7, r8, fp}
 80001f0:	e8ac 09c0 	stmia.w	ip!, {r6, r7, r8, fp}
 80001f4:	e8ac 09c0 	stmia.w	ip!, {r6, r7, r8, fp}
 80001f8:	468d      	mov	sp, r1
 80001fa:	4770      	bx	lr

080001fc <exit>:
 80001fc:	b510      	push	{r4, lr}
 80001fe:	4604      	mov	r4, r0
 8000200:	f3af 8000 	nop.w
 8000204:	4620      	mov	r0, r4
 8000206:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
 800020a:	f7ff bfa8 	b.w	800015e <__rt_exit>
	...

08000210 <__user_libspace>:
 8000210:	4800      	ldr	r0, [pc, #0]	@ (8000214 <__user_libspace+0x4>)
 8000212:	4770      	bx	lr
 8000214:	20000000 	.word	0x20000000

08000218 <_sys_exit>:
 8000218:	4901      	ldr	r1, [pc, #4]	@ (8000220 <_sys_exit+0x8>)
 800021a:	2018      	movs	r0, #24
 800021c:	beab      	bkpt	0x00ab
 800021e:	e7fe      	b.n	800021e <_sys_exit+0x6>
 8000220:	00020026 	.word	0x00020026

08000224 <__use_no_semihosting_swi>:
 8000224:	4770      	bx	lr

08000226 <__semihosting_library_function>:
 8000226:	b510      	push	{r4, lr}
 8000228:	f000 f802 	bl	8000230 <SetSysClockTo72>
 800022c:	bd10      	pop	{r4, pc}
	...

08000230 <SetSysClockTo72>:
 8000230:	b50c      	push	{r2, r3, lr}
 8000232:	2000      	movs	r0, #0
 8000234:	9001      	str	r0, [sp, #4]
 8000236:	9000      	str	r0, [sp, #0]
 8000238:	4833      	ldr	r0, [pc, #204]	@ (8000308 <SetSysClockTo72+0xd8>)
 800023a:	6800      	ldr	r0, [r0, #0]
 800023c:	f440 3080 	orr.w	r0, r0, #65536	@ 0x10000
 8000240:	4931      	ldr	r1, [pc, #196]	@ (8000308 <SetSysClockTo72+0xd8>)
 8000242:	6008      	str	r0, [r1, #0]
 8000244:	bf00      	nop
 8000246:	4830      	ldr	r0, [pc, #192]	@ (8000308 <SetSysClockTo72+0xd8>)
 8000248:	6800      	ldr	r0, [r0, #0]
 800024a:	f400 3000 	and.w	r0, r0, #131072	@ 0x20000
 800024e:	9000      	str	r0, [sp, #0]
 8000250:	9801      	ldr	r0, [sp, #4]
 8000252:	1c40      	adds	r0, r0, #1
 8000254:	9001      	str	r0, [sp, #4]
 8000256:	9800      	ldr	r0, [sp, #0]
 8000258:	b918      	cbnz	r0, 8000262 <SetSysClockTo72+0x32>
 800025a:	9801      	ldr	r0, [sp, #4]
 800025c:	f5b0 6fa0 	cmp.w	r0, #1280	@ 0x500
 8000260:	d1f1      	bne.n	8000246 <SetSysClockTo72+0x16>
 8000262:	4829      	ldr	r0, [pc, #164]	@ (8000308 <SetSysClockTo72+0xd8>)
 8000264:	6800      	ldr	r0, [r0, #0]
 8000266:	f400 3000 	and.w	r0, r0, #131072	@ 0x20000
 800026a:	b110      	cbz	r0, 8000272 <SetSysClockTo72+0x42>
 800026c:	2001      	movs	r0, #1
 800026e:	9000      	str	r0, [sp, #0]
 8000270:	e001      	b.n	8000276 <SetSysClockTo72+0x46>
 8000272:	2000      	movs	r0, #0
 8000274:	9000      	str	r0, [sp, #0]
 8000276:	9800      	ldr	r0, [sp, #0]
 8000278:	2801      	cmp	r0, #1
 800027a:	d143      	bne.n	8000304 <SetSysClockTo72+0xd4>
 800027c:	4823      	ldr	r0, [pc, #140]	@ (800030c <SetSysClockTo72+0xdc>)
 800027e:	6800      	ldr	r0, [r0, #0]
 8000280:	f040 0010 	orr.w	r0, r0, #16
 8000284:	4921      	ldr	r1, [pc, #132]	@ (800030c <SetSysClockTo72+0xdc>)
 8000286:	6008      	str	r0, [r1, #0]
 8000288:	4608      	mov	r0, r1
 800028a:	6800      	ldr	r0, [r0, #0]
 800028c:	f020 0003 	bic.w	r0, r0, #3
 8000290:	6008      	str	r0, [r1, #0]
 8000292:	4608      	mov	r0, r1
 8000294:	6800      	ldr	r0, [r0, #0]
 8000296:	f040 0002 	orr.w	r0, r0, #2
 800029a:	6008      	str	r0, [r1, #0]
 800029c:	481a      	ldr	r0, [pc, #104]	@ (8000308 <SetSysClockTo72+0xd8>)
 800029e:	6840      	ldr	r0, [r0, #4]
 80002a0:	4919      	ldr	r1, [pc, #100]	@ (8000308 <SetSysClockTo72+0xd8>)
 80002a2:	6048      	str	r0, [r1, #4]
 80002a4:	4608      	mov	r0, r1
 80002a6:	6840      	ldr	r0, [r0, #4]
 80002a8:	6048      	str	r0, [r1, #4]
 80002aa:	4608      	mov	r0, r1
 80002ac:	6840      	ldr	r0, [r0, #4]
 80002ae:	f440 6080 	orr.w	r0, r0, #1024	@ 0x400
 80002b2:	6048      	str	r0, [r1, #4]
 80002b4:	4608      	mov	r0, r1
 80002b6:	6840      	ldr	r0, [r0, #4]
 80002b8:	f420 107c 	bic.w	r0, r0, #4128768	@ 0x3f0000
 80002bc:	6048      	str	r0, [r1, #4]
 80002be:	4608      	mov	r0, r1
 80002c0:	6840      	ldr	r0, [r0, #4]
 80002c2:	f440 10e8 	orr.w	r0, r0, #1900544	@ 0x1d0000
 80002c6:	6048      	str	r0, [r1, #4]
 80002c8:	4608      	mov	r0, r1
 80002ca:	6800      	ldr	r0, [r0, #0]
 80002cc:	f040 7080 	orr.w	r0, r0, #16777216	@ 0x1000000
 80002d0:	6008      	str	r0, [r1, #0]
 80002d2:	bf00      	nop
 80002d4:	480c      	ldr	r0, [pc, #48]	@ (8000308 <SetSysClockTo72+0xd8>)
 80002d6:	6800      	ldr	r0, [r0, #0]
 80002d8:	f000 7000 	and.w	r0, r0, #33554432	@ 0x2000000
 80002dc:	2800      	cmp	r0, #0
 80002de:	d0f9      	beq.n	80002d4 <SetSysClockTo72+0xa4>
 80002e0:	4809      	ldr	r0, [pc, #36]	@ (8000308 <SetSysClockTo72+0xd8>)
 80002e2:	6840      	ldr	r0, [r0, #4]
 80002e4:	f020 0003 	bic.w	r0, r0, #3
 80002e8:	4907      	ldr	r1, [pc, #28]	@ (8000308 <SetSysClockTo72+0xd8>)
 80002ea:	6048      	str	r0, [r1, #4]
 80002ec:	4608      	mov	r0, r1
 80002ee:	6840      	ldr	r0, [r0, #4]
 80002f0:	f040 0002 	orr.w	r0, r0, #2
 80002f4:	6048      	str	r0, [r1, #4]
 80002f6:	bf00      	nop
 80002f8:	4803      	ldr	r0, [pc, #12]	@ (8000308 <SetSysClockTo72+0xd8>)
 80002fa:	6840      	ldr	r0, [r0, #4]
 80002fc:	f000 000c 	and.w	r0, r0, #12
 8000300:	2808      	cmp	r0, #8
 8000302:	d1f9      	bne.n	80002f8 <SetSysClockTo72+0xc8>
 8000304:	bd0c      	pop	{r2, r3, pc}
 8000306:	0000      	.short	0x0000
 8000308:	40021000 	.word	0x40021000
 800030c:	40022000 	.word	0x40022000

08000310 <SystemInit>:
 8000310:	b510      	push	{r4, lr}
 8000312:	4813      	ldr	r0, [pc, #76]	@ (8000360 <SystemInit+0x50>)
 8000314:	6800      	ldr	r0, [r0, #0]
 8000316:	f040 0001 	orr.w	r0, r0, #1
 800031a:	4911      	ldr	r1, [pc, #68]	@ (8000360 <SystemInit+0x50>)
 800031c:	6008      	str	r0, [r1, #0]
 800031e:	4608      	mov	r0, r1
 8000320:	6840      	ldr	r0, [r0, #4]
 8000322:	4910      	ldr	r1, [pc, #64]	@ (8000364 <SystemInit+0x54>)
 8000324:	4008      	ands	r0, r1
 8000326:	490e      	ldr	r1, [pc, #56]	@ (8000360 <SystemInit+0x50>)
 8000328:	6048      	str	r0, [r1, #4]
 800032a:	4608      	mov	r0, r1
 800032c:	6800      	ldr	r0, [r0, #0]
 800032e:	490e      	ldr	r1, [pc, #56]	@ (8000368 <SystemInit+0x58>)
 8000330:	4008      	ands	r0, r1
 8000332:	490b      	ldr	r1, [pc, #44]	@ (8000360 <SystemInit+0x50>)
 8000334:	6008      	str	r0, [r1, #0]
 8000336:	4608      	mov	r0, r1
 8000338:	6800      	ldr	r0, [r0, #0]
 800033a:	f420 2080 	bic.w	r0, r0, #262144	@ 0x40000
 800033e:	6008      	str	r0, [r1, #0]
 8000340:	4608      	mov	r0, r1
 8000342:	6840      	ldr	r0, [r0, #4]
 8000344:	f420 00fe 	bic.w	r0, r0, #8323072	@ 0x7f0000
 8000348:	6048      	str	r0, [r1, #4]
 800034a:	f44f 001f 	mov.w	r0, #10420224	@ 0x9f0000
 800034e:	6088      	str	r0, [r1, #8]
 8000350:	f7ff ff69 	bl	8000226 <__semihosting_library_function>
 8000354:	f04f 6000 	mov.w	r0, #134217728	@ 0x8000000
 8000358:	4904      	ldr	r1, [pc, #16]	@ (800036c <SystemInit+0x5c>)
 800035a:	6008      	str	r0, [r1, #0]
 800035c:	bd10      	pop	{r4, pc}
 800035e:	0000      	.short	0x0000
 8000360:	40021000 	.word	0x40021000
 8000364:	f8ff0000 	.word	0xf8ff0000
 8000368:	fef6ffff 	.word	0xfef6ffff
 800036c:	e000ed08 	.word	0xe000ed08

08000370 <main>:
 8000370:	2001      	movs	r0, #1
 8000372:	4904      	ldr	r1, [pc, #16]	@ (8000384 <main+0x14>)
 8000374:	6188      	str	r0, [r1, #24]
 8000376:	2000      	movs	r0, #0
 8000378:	4903      	ldr	r1, [pc, #12]	@ (8000388 <main+0x18>)
 800037a:	6048      	str	r0, [r1, #4]
 800037c:	60c8      	str	r0, [r1, #12]
 800037e:	bf00      	nop
 8000380:	e7fe      	b.n	8000380 <main+0x10>
 8000382:	0000      	.short	0x0000
 8000384:	40021000 	.word	0x40021000
 8000388:	40011000 	.word	0x40011000

0800038c <Region$$Table$$Base>:
 800038c:	0800039c 	.word	0x0800039c
 8000390:	20000000 	.word	0x20000000
 8000394:	00000660 	.word	0x00000660
 8000398:	08000128 	.word	0x08000128
