   0:	eb 63                	jmp    0x65
   2:	90                   	nop
   3:	d0 bc 00 7c 8e c0 8e 	sarb   -0x713f7184(%eax,%eax,1)
   a:	d8 be 00 7c bf 00    	fdivrs 0xbf7c00(%esi)
  10:	06                   	push   %es
  11:	b9 00 02 fc f3       	mov    $0xf3fc0200,%ecx
  16:	a4                   	movsb  %ds:(%esi),%es:(%edi)
  17:	50                   	push   %eax
  18:	68 1c 06 cb fb       	push   $0xfbcb061c
  1d:	b9 04 00 bd be       	mov    $0xbebd0004,%ecx
  22:	07                   	pop    %es
  23:	80 7e 00 00          	cmpb   $0x0,0x0(%esi)
  27:	7c 0b                	jl     0x34
  29:	0f 85 0e 01 83 c5    	jne    0xc583013d
  2f:	10 e2                	adc    %ah,%dl
  31:	f1                   	icebp
  32:	cd 18                	int    $0x18
  34:	88 56 00             	mov    %dl,0x0(%esi)
  37:	55                   	push   %ebp
  38:	c6 46 11 05          	movb   $0x5,0x11(%esi)
  3c:	c6 46 10 00          	movb   $0x0,0x10(%esi)
  40:	b4 41                	mov    $0x41,%ah
  42:	bb aa 55 cd 13       	mov    $0x13cd55aa,%ebx
  47:	5d                   	pop    %ebp
  48:	72 0f                	jb     0x59
  4a:	81 fb 55 aa 75 09    	cmp    $0x975aa55,%ebx
  50:	f7 c1 01 00 74 03    	test   $0x3740001,%ecx
  56:	fe 46 10             	incb   0x10(%esi)
  59:	66 00 80 01 00 00 00 	data16 add %al,0x1(%eax)
  60:	00 00                	add    %al,(%eax)
  62:	00 00                	add    %al,(%eax)
  64:	ff                   	(bad)
  65:	fa                   	cli
  66:	90                   	nop
  67:	90                   	nop
  68:	f6 c2 80             	test   $0x80,%dl
  6b:	74 05                	je     0x72
  6d:	f6 c2 70             	test   $0x70,%dl
  70:	74 02                	je     0x74
  72:	b2 80                	mov    $0x80,%dl
  74:	ea 79 7c 00 00 31 c0 	ljmp   $0xc031,$0x7c79
  7b:	8e d8                	mov    %eax,%ds
  7d:	8e d0                	mov    %eax,%ss
  7f:	bc 00 20 fb a0       	mov    $0xa0fb2000,%esp
  84:	64 7c 3c             	fs jl  0xc3
  87:	ff 74 02 88          	pushl  -0x78(%edx,%eax,1)
  8b:	c2 52 bb             	ret    $0xbb52
  8e:	17                   	pop    %ss
  8f:	04 f6                	add    $0xf6,%al
  91:	07                   	pop    %es
  92:	03 74 06 be          	add    -0x42(%esi,%eax,1),%esi
  96:	88 7d e8             	mov    %bh,-0x18(%ebp)
  99:	17                   	pop    %ss
  9a:	01 be 05 7c b4 41    	add    %edi,0x41b47c05(%esi)
  a0:	bb aa 55 cd 13       	mov    $0x13cd55aa,%ebx
  a5:	5a                   	pop    %edx
  a6:	52                   	push   %edx
  a7:	72 3d                	jb     0xe6
  a9:	81 fb 55 aa 75 37    	cmp    $0x3775aa55,%ebx
  af:	83 e1 01             	and    $0x1,%ecx
  b2:	74 32                	je     0xe6
  b4:	31 c0                	xor    %eax,%eax
  b6:	89 44 04 40          	mov    %eax,0x40(%esp,%eax,1)
  ba:	88 44 ff 89          	mov    %al,-0x77(%edi,%edi,8)
  be:	44                   	inc    %esp
  bf:	02 c7                	add    %bh,%al
  c1:	04 10                	add    $0x10,%al
  c3:	00 66 8b             	add    %ah,-0x75(%esi)
  c6:	1e                   	push   %ds
  c7:	5c                   	pop    %esp
  c8:	7c 66                	jl     0x130
  ca:	89 5c 08 66          	mov    %ebx,0x66(%eax,%ecx,1)
  ce:	8b 1e                	mov    (%esi),%ebx
  d0:	60                   	pusha
  d1:	7c 66                	jl     0x139
  d3:	89 5c 0c c7          	mov    %ebx,-0x39(%esp,%ecx,1)
  d7:	44                   	inc    %esp
  d8:	06                   	push   %es
  d9:	00 70 b4             	add    %dh,-0x4c(%eax)
  dc:	42                   	inc    %edx
  dd:	cd 13                	int    $0x13
  df:	72 05                	jb     0xe6
  e1:	bb 00 70 eb 76       	mov    $0x76eb7000,%ebx
  e6:	b4 08                	mov    $0x8,%ah
  e8:	cd 13                	int    $0x13
  ea:	73 0d                	jae    0xf9
  ec:	5a                   	pop    %edx
  ed:	84 d2                	test   %dl,%dl
  ef:	0f 83 d0 00 be 93    	jae    0x93be01c5
  f5:	7d e9                	jge    0xe0
  f7:	82 00 66             	addb   $0x66,(%eax)
  fa:	0f b6 c6             	movzbl %dh,%eax
  fd:	88 64 ff 40          	mov    %ah,0x40(%edi,%edi,8)
 101:	66 89 44 04 0f       	mov    %ax,0xf(%esp,%eax,1)
 106:	b6 d1                	mov    $0xd1,%dh
 108:	c1 e2 02             	shl    $0x2,%edx
 10b:	88 e8                	mov    %ch,%al
 10d:	88 f4                	mov    %dh,%ah
 10f:	40                   	inc    %eax
 110:	89 44 08 0f          	mov    %eax,0xf(%eax,%ecx,1)
 114:	b6 c2                	mov    $0xc2,%dh
 116:	c0 e8 02             	shr    $0x2,%al
 119:	66 89 04 66          	mov    %ax,(%esi,%eiz,2)
 11d:	a1 60 7c 66 09       	mov    0x9667c60,%eax
 122:	c0 75 4e 66          	shlb   $0x66,0x4e(%ebp)
 126:	a1 5c 7c 66 31       	mov    0x31667c5c,%eax
 12b:	d2 66 f7             	shlb   %cl,-0x9(%esi)
 12e:	34 88                	xor    $0x88,%al
 130:	d1 31                	shll   (%ecx)
 132:	d2 66 f7             	shlb   %cl,-0x9(%esi)
 135:	74 04                	je     0x13b
 137:	3b 44 08 7d          	cmp    0x7d(%eax,%ecx,1),%eax
 13b:	37                   	aaa
 13c:	fe c1                	inc    %cl
 13e:	88 c5                	mov    %al,%ch
 140:	30 c0                	xor    %al,%al
 142:	c1 e8 02             	shr    $0x2,%eax
 145:	08 c1                	or     %al,%cl
 147:	88 d0                	mov    %dl,%al
 149:	5a                   	pop    %edx
 14a:	88 c6                	mov    %al,%dh
 14c:	bb 00 70 8e c3       	mov    $0xc38e7000,%ebx
 151:	31 db                	xor    %ebx,%ebx
 153:	b8 01 02 cd 13       	mov    $0x13cd0201,%eax
 158:	72 1e                	jb     0x178
 15a:	8c c3                	mov    %es,%ebx
 15c:	60                   	pusha
 15d:	1e                   	push   %ds
 15e:	b9 00 01 8e db       	mov    $0xdb8e0100,%ecx
 163:	31 f6                	xor    %esi,%esi
 165:	bf 00 80 8e c6       	mov    $0xc68e8000,%edi
 16a:	fc                   	cld
 16b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 16d:	1f                   	pop    %ds
 16e:	61                   	popa
 16f:	ff 26                	jmp    *(%esi)
 171:	5a                   	pop    %edx
 172:	7c be                	jl     0x132
 174:	8e 7d eb             	mov    -0x15(%ebp),%?
 177:	03 be 9d 7d e8 34    	add    0x34e87d9d(%esi),%edi
 17d:	00 be a2 7d e8 2e    	add    %bh,0x2ee87da2(%esi)
 183:	00 cd                	add    %cl,%ch
 185:	18 eb                	sbb    %ch,%bl
 187:	fe 47 52             	incb   0x52(%edi)
 18a:	55                   	push   %ebp
 18b:	42                   	inc    %edx
 18c:	20 00                	and    %al,(%eax)
 18e:	47                   	inc    %edi
 18f:	65 6f                	outsl  %gs:(%esi),(%dx)
 191:	6d                   	insl   (%dx),%es:(%edi)
 192:	00 48 61             	add    %cl,0x61(%eax)
 195:	72 64                	jb     0x1fb
 197:	20 44 69 73          	and    %al,0x73(%ecx,%ebp,2)
 19b:	6b 00 52             	imul   $0x52,(%eax),%eax
 19e:	65 61                	gs popa
 1a0:	64 00 20             	add    %ah,%fs:(%eax)
 1a3:	45                   	inc    %ebp
 1a4:	72 72                	jb     0x218
 1a6:	6f                   	outsl  %ds:(%esi),(%dx)
 1a7:	72 0d                	jb     0x1b6
 1a9:	0a 00                	or     (%eax),%al
 1ab:	bb 01 00 b4 0e       	mov    $0xeb40001,%ebx
 1b0:	cd 10                	int    $0x10
 1b2:	ac                   	lods   %ds:(%esi),%al
 1b3:	3c 00                	cmp    $0x0,%al
 1b5:	75 f4                	jne    0x1ab
 1b7:	c3                   	ret
 1b8:	70 f6                	jo     0x1b0
 1ba:	a9                   	.byte 0xa9
 1bb:	cf                   	iret