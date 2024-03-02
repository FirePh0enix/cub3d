
cub3D:     file format elf64-x86-64


Disassembly of section .text:

00000000000023a0 <_start>:
    23a0:	f3 0f 1e fa          	endbr64
    23a4:	31 ed                	xor    ebp,ebp
    23a6:	49 89 d1             	mov    r9,rdx
    23a9:	5e                   	pop    rsi
    23aa:	48 89 e2             	mov    rdx,rsp
    23ad:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    23b1:	50                   	push   rax
    23b2:	54                   	push   rsp
    23b3:	45 31 c0             	xor    r8d,r8d
    23b6:	31 c9                	xor    ecx,ecx
    23b8:	48 8d 3d e1 00 00 00 	lea    rdi,[rip+0xe1]        # 24a0 <main>
    23bf:	ff 15 1b 3c 00 00    	call   QWORD PTR [rip+0x3c1b]        # 5fe0 <__libc_start_main@GLIBC_2.34>
    23c5:	f4                   	hlt
    23c6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    23cd:	00 00 00 
    23d0:	48 8d 3d 29 3f 00 00 	lea    rdi,[rip+0x3f29]        # 6300 <__TMC_END__>
    23d7:	48 8d 05 22 3f 00 00 	lea    rax,[rip+0x3f22]        # 6300 <__TMC_END__>
    23de:	48 39 f8             	cmp    rax,rdi
    23e1:	74 15                	je     23f8 <_start+0x58>
    23e3:	48 8b 05 de 3b 00 00 	mov    rax,QWORD PTR [rip+0x3bde]        # 5fc8 <_ITM_deregisterTMCloneTable@Base>
    23ea:	48 85 c0             	test   rax,rax
    23ed:	74 09                	je     23f8 <_start+0x58>
    23ef:	ff e0                	jmp    rax
    23f1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    23f8:	c3                   	ret
    23f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2400:	48 8d 3d f9 3e 00 00 	lea    rdi,[rip+0x3ef9]        # 6300 <__TMC_END__>
    2407:	48 8d 35 f2 3e 00 00 	lea    rsi,[rip+0x3ef2]        # 6300 <__TMC_END__>
    240e:	48 29 fe             	sub    rsi,rdi
    2411:	48 89 f0             	mov    rax,rsi
    2414:	48 c1 ee 3f          	shr    rsi,0x3f
    2418:	48 c1 f8 03          	sar    rax,0x3
    241c:	48 01 c6             	add    rsi,rax
    241f:	48 d1 fe             	sar    rsi,1
    2422:	74 14                	je     2438 <_start+0x98>
    2424:	48 8b 05 a5 3b 00 00 	mov    rax,QWORD PTR [rip+0x3ba5]        # 5fd0 <_ITM_registerTMCloneTable@Base>
    242b:	48 85 c0             	test   rax,rax
    242e:	74 08                	je     2438 <_start+0x98>
    2430:	ff e0                	jmp    rax
    2432:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2438:	c3                   	ret
    2439:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2440:	f3 0f 1e fa          	endbr64
    2444:	80 3d b5 3e 00 00 00 	cmp    BYTE PTR [rip+0x3eb5],0x0        # 6300 <__TMC_END__>
    244b:	75 33                	jne    2480 <_start+0xe0>
    244d:	55                   	push   rbp
    244e:	48 83 3d 82 3b 00 00 	cmp    QWORD PTR [rip+0x3b82],0x0        # 5fd8 <__cxa_finalize@GLIBC_2.2.5>
    2455:	00 
    2456:	48 89 e5             	mov    rbp,rsp
    2459:	74 0d                	je     2468 <_start+0xc8>
    245b:	48 8b 3d 66 3d 00 00 	mov    rdi,QWORD PTR [rip+0x3d66]        # 61c8 <__dso_handle>
    2462:	ff 15 70 3b 00 00    	call   QWORD PTR [rip+0x3b70]        # 5fd8 <__cxa_finalize@GLIBC_2.2.5>
    2468:	e8 63 ff ff ff       	call   23d0 <_start+0x30>
    246d:	c6 05 8c 3e 00 00 01 	mov    BYTE PTR [rip+0x3e8c],0x1        # 6300 <__TMC_END__>
    2474:	5d                   	pop    rbp
    2475:	c3                   	ret
    2476:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    247d:	00 00 00 
    2480:	c3                   	ret
    2481:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    2488:	00 00 00 00 
    248c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    2490:	f3 0f 1e fa          	endbr64
    2494:	e9 67 ff ff ff       	jmp    2400 <_start+0x60>
    2499:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000024a0 <main>:
    24a0:	41 57                	push   r15
    24a2:	41 56                	push   r14
    24a4:	41 55                	push   r13
    24a6:	41 54                	push   r12
    24a8:	53                   	push   rbx
    24a9:	48 81 ec d0 00 00 00 	sub    rsp,0xd0
    24b0:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    24b7:	00 00 
    24b9:	48 89 84 24 c8 00 00 	mov    QWORD PTR [rsp+0xc8],rax
    24c0:	00 
    24c1:	48 8d 35 a8 1b 00 00 	lea    rsi,[rip+0x1ba8]        # 4070 <_IO_stdin_used+0x70>
    24c8:	4c 8d 7c 24 30       	lea    r15,[rsp+0x30]
    24cd:	ba 90 00 00 00       	mov    edx,0x90
    24d2:	4c 89 ff             	mov    rdi,r15
    24d5:	e8 86 fe ff ff       	call   2360 <memcpy@plt>
    24da:	31 c0                	xor    eax,eax
    24dc:	e8 af 08 00 00       	call   2d90 <mlx_init>
    24e1:	48 89 c3             	mov    rbx,rax
    24e4:	48 8d 0d 15 1c 00 00 	lea    rcx,[rip+0x1c15]        # 4100 <_IO_stdin_used+0x100>
    24eb:	48 89 c7             	mov    rdi,rax
    24ee:	be 00 05 00 00       	mov    esi,0x500
    24f3:	ba d0 02 00 00       	mov    edx,0x2d0
    24f8:	e8 d3 09 00 00       	call   2ed0 <mlx_new_window>
    24fd:	49 89 c6             	mov    r14,rax
    2500:	be 03 00 00 00       	mov    esi,0x3
    2505:	4c 89 ff             	mov    rdi,r15
    2508:	e8 23 02 00 00       	call   2730 <mesh_load_from_data>
    250d:	49 89 c7             	mov    r15,rax
    2510:	48 8d 0d b9 01 00 00 	lea    rcx,[rip+0x1b9]        # 26d0 <close_hook>
    2517:	4c 89 f7             	mov    rdi,r14
    251a:	be 11 00 00 00       	mov    esi,0x11
    251f:	31 d2                	xor    edx,edx
    2521:	49 89 d8             	mov    r8,rbx
    2524:	e8 67 1a 00 00       	call   3f90 <mlx_hook>
    2529:	49 89 e4             	mov    r12,rsp
    252c:	4c 89 e7             	mov    rdi,r12
    252f:	48 89 de             	mov    rsi,rbx
    2532:	ba 00 05 00 00       	mov    edx,0x500
    2537:	b9 d0 02 00 00       	mov    ecx,0x2d0
    253c:	e8 9f 01 00 00       	call   26e0 <r3d_init>
    2541:	e8 0a fd ff ff       	call   2250 <clock@plt>
    2546:	49 89 c5             	mov    r13,rax
    2549:	4c 89 e7             	mov    rdi,r12
    254c:	4c 89 fe             	mov    rsi,r15
    254f:	e8 8c 02 00 00       	call   27e0 <r3d_draw_scene>
    2554:	4c 89 e7             	mov    rdi,r12
    2557:	4c 89 fe             	mov    rsi,r15
    255a:	e8 81 02 00 00       	call   27e0 <r3d_draw_scene>
    255f:	4c 89 e7             	mov    rdi,r12
    2562:	4c 89 fe             	mov    rsi,r15
    2565:	e8 76 02 00 00       	call   27e0 <r3d_draw_scene>
    256a:	4c 89 e7             	mov    rdi,r12
    256d:	4c 89 fe             	mov    rsi,r15
    2570:	e8 6b 02 00 00       	call   27e0 <r3d_draw_scene>
    2575:	4c 89 e7             	mov    rdi,r12
    2578:	4c 89 fe             	mov    rsi,r15
    257b:	e8 60 02 00 00       	call   27e0 <r3d_draw_scene>
    2580:	4c 89 e7             	mov    rdi,r12
    2583:	4c 89 fe             	mov    rsi,r15
    2586:	e8 55 02 00 00       	call   27e0 <r3d_draw_scene>
    258b:	4c 89 e7             	mov    rdi,r12
    258e:	4c 89 fe             	mov    rsi,r15
    2591:	e8 4a 02 00 00       	call   27e0 <r3d_draw_scene>
    2596:	4c 89 e7             	mov    rdi,r12
    2599:	4c 89 fe             	mov    rsi,r15
    259c:	e8 3f 02 00 00       	call   27e0 <r3d_draw_scene>
    25a1:	4c 89 e7             	mov    rdi,r12
    25a4:	4c 89 fe             	mov    rsi,r15
    25a7:	e8 34 02 00 00       	call   27e0 <r3d_draw_scene>
    25ac:	4c 89 e7             	mov    rdi,r12
    25af:	4c 89 fe             	mov    rsi,r15
    25b2:	e8 29 02 00 00       	call   27e0 <r3d_draw_scene>
    25b7:	4c 89 e7             	mov    rdi,r12
    25ba:	4c 89 fe             	mov    rsi,r15
    25bd:	e8 1e 02 00 00       	call   27e0 <r3d_draw_scene>
    25c2:	4c 89 e7             	mov    rdi,r12
    25c5:	4c 89 fe             	mov    rsi,r15
    25c8:	e8 13 02 00 00       	call   27e0 <r3d_draw_scene>
    25cd:	4c 89 e7             	mov    rdi,r12
    25d0:	4c 89 fe             	mov    rsi,r15
    25d3:	e8 08 02 00 00       	call   27e0 <r3d_draw_scene>
    25d8:	4c 89 e7             	mov    rdi,r12
    25db:	4c 89 fe             	mov    rsi,r15
    25de:	e8 fd 01 00 00       	call   27e0 <r3d_draw_scene>
    25e3:	4c 89 e7             	mov    rdi,r12
    25e6:	4c 89 fe             	mov    rsi,r15
    25e9:	e8 f2 01 00 00       	call   27e0 <r3d_draw_scene>
    25ee:	4c 89 e7             	mov    rdi,r12
    25f1:	4c 89 fe             	mov    rsi,r15
    25f4:	e8 e7 01 00 00       	call   27e0 <r3d_draw_scene>
    25f9:	4c 89 e7             	mov    rdi,r12
    25fc:	4c 89 fe             	mov    rsi,r15
    25ff:	e8 dc 01 00 00       	call   27e0 <r3d_draw_scene>
    2604:	4c 89 e7             	mov    rdi,r12
    2607:	4c 89 fe             	mov    rsi,r15
    260a:	e8 d1 01 00 00       	call   27e0 <r3d_draw_scene>
    260f:	4c 89 e7             	mov    rdi,r12
    2612:	4c 89 fe             	mov    rsi,r15
    2615:	e8 c6 01 00 00       	call   27e0 <r3d_draw_scene>
    261a:	4c 89 e7             	mov    rdi,r12
    261d:	4c 89 fe             	mov    rsi,r15
    2620:	e8 bb 01 00 00       	call   27e0 <r3d_draw_scene>
    2625:	e8 26 fc ff ff       	call   2250 <clock@plt>
    262a:	4c 29 e8             	sub    rax,r13
    262d:	f2 48 0f 2a c0       	cvtsi2sd xmm0,rax
    2632:	f2 0f 5e 05 d6 19 00 	divsd  xmm0,QWORD PTR [rip+0x19d6]        # 4010 <_IO_stdin_used+0x10>
    2639:	00 
    263a:	f2 0f 59 05 d6 19 00 	mulsd  xmm0,QWORD PTR [rip+0x19d6]        # 4018 <_IO_stdin_used+0x18>
    2641:	00 
    2642:	f2 0f 5e 05 d6 19 00 	divsd  xmm0,QWORD PTR [rip+0x19d6]        # 4020 <_IO_stdin_used+0x20>
    2649:	00 
    264a:	48 8d 3d b5 1a 00 00 	lea    rdi,[rip+0x1ab5]        # 4106 <_IO_stdin_used+0x106>
    2651:	48 8d 35 ca 1a 00 00 	lea    rsi,[rip+0x1aca]        # 4122 <_IO_stdin_used+0x122>
    2658:	b0 01                	mov    al,0x1
    265a:	e8 d1 f9 ff ff       	call   2030 <printf@plt>
    265f:	48 8b 14 24          	mov    rdx,QWORD PTR [rsp]
    2663:	48 89 df             	mov    rdi,rbx
    2666:	4c 89 f6             	mov    rsi,r14
    2669:	31 c9                	xor    ecx,ecx
    266b:	45 31 c0             	xor    r8d,r8d
    266e:	e8 3d 11 00 00       	call   37b0 <mlx_put_image_to_window>
    2673:	48 89 df             	mov    rdi,rbx
    2676:	e8 c5 09 00 00       	call   3040 <mlx_loop>
    267b:	48 89 df             	mov    rdi,rbx
    267e:	4c 89 f6             	mov    rsi,r14
    2681:	e8 6a 12 00 00       	call   38f0 <mlx_destroy_window>
    2686:	48 89 df             	mov    rdi,rbx
    2689:	e8 52 19 00 00       	call   3fe0 <mlx_destroy_display>
    268e:	48 89 df             	mov    rdi,rbx
    2691:	e8 ba fa ff ff       	call   2150 <free@plt>
    2696:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    269d:	00 00 
    269f:	48 3b 84 24 c8 00 00 	cmp    rax,QWORD PTR [rsp+0xc8]
    26a6:	00 
    26a7:	75 13                	jne    26bc <main+0x21c>
    26a9:	31 c0                	xor    eax,eax
    26ab:	48 81 c4 d0 00 00 00 	add    rsp,0xd0
    26b2:	5b                   	pop    rbx
    26b3:	41 5c                	pop    r12
    26b5:	41 5d                	pop    r13
    26b7:	41 5e                	pop    r14
    26b9:	41 5f                	pop    r15
    26bb:	c3                   	ret
    26bc:	e8 af fb ff ff       	call   2270 <__stack_chk_fail@plt>
    26c1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]
    26c8:	0f 1f 84 00 00 00 00 
    26cf:	00 

00000000000026d0 <close_hook>:
    26d0:	e9 5b 09 00 00       	jmp    3030 <mlx_loop_end>
    26d5:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    26dc:	00 00 00 
    26df:	90                   	nop

00000000000026e0 <r3d_init>:
    26e0:	55                   	push   rbp
    26e1:	41 56                	push   r14
    26e3:	53                   	push   rbx
    26e4:	89 cb                	mov    ebx,ecx
    26e6:	89 d5                	mov    ebp,edx
    26e8:	49 89 fe             	mov    r14,rdi
    26eb:	48 89 f7             	mov    rdi,rsi
    26ee:	89 d6                	mov    esi,edx
    26f0:	89 ca                	mov    edx,ecx
    26f2:	e8 19 10 00 00       	call   3710 <mlx_new_image>
    26f7:	49 89 06             	mov    QWORD PTR [r14],rax
    26fa:	48 8b 40 30          	mov    rax,QWORD PTR [rax+0x30]
    26fe:	49 89 46 08          	mov    QWORD PTR [r14+0x8],rax
    2702:	41 89 6e 10          	mov    DWORD PTR [r14+0x10],ebp
    2706:	41 89 5e 14          	mov    DWORD PTR [r14+0x14],ebx
    270a:	f3 0f 10 05 f2 18 00 	movss  xmm0,DWORD PTR [rip+0x18f2]        # 4004 <_IO_stdin_used+0x4>
    2711:	00 
    2712:	41 0f 11 46 1c       	movups XMMWORD PTR [r14+0x1c],xmm0
    2717:	41 c7 46 18 01 00 00 	mov    DWORD PTR [r14+0x18],0x1
    271e:	00 
    271f:	5b                   	pop    rbx
    2720:	41 5e                	pop    r14
    2722:	5d                   	pop    rbp
    2723:	c3                   	ret
    2724:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    272b:	00 00 00 
    272e:	66 90                	xchg   ax,ax

0000000000002730 <mesh_load_from_data>:
    2730:	41 57                	push   r15
    2732:	41 56                	push   r14
    2734:	53                   	push   rbx
    2735:	49 89 f7             	mov    r15,rsi
    2738:	48 89 fb             	mov    rbx,rdi
    273b:	bf 10 00 00 00       	mov    edi,0x10
    2740:	e8 9b f9 ff ff       	call   20e0 <malloc@plt>
    2745:	49 89 c6             	mov    r14,rax
    2748:	4c 89 78 08          	mov    QWORD PTR [rax+0x8],r15
    274c:	4c 89 ff             	mov    rdi,r15
    274f:	48 c1 e7 04          	shl    rdi,0x4
    2753:	e8 88 f9 ff ff       	call   20e0 <malloc@plt>
    2758:	49 89 06             	mov    QWORD PTR [r14],rax
    275b:	4d 85 ff             	test   r15,r15
    275e:	74 51                	je     27b1 <mesh_load_from_data+0x81>
    2760:	49 83 ff 01          	cmp    r15,0x1
    2764:	75 04                	jne    276a <mesh_load_from_data+0x3a>
    2766:	31 c9                	xor    ecx,ecx
    2768:	eb 35                	jmp    279f <mesh_load_from_data+0x6f>
    276a:	4c 89 fa             	mov    rdx,r15
    276d:	48 83 e2 fe          	and    rdx,0xfffffffffffffffe
    2771:	be 10 00 00 00       	mov    esi,0x10
    2776:	31 c9                	xor    ecx,ecx
    2778:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    277f:	00 
    2780:	0f 28 44 33 f0       	movaps xmm0,XMMWORD PTR [rbx+rsi*1-0x10]
    2785:	0f 29 44 30 f0       	movaps XMMWORD PTR [rax+rsi*1-0x10],xmm0
    278a:	0f 28 04 33          	movaps xmm0,XMMWORD PTR [rbx+rsi*1]
    278e:	0f 29 04 30          	movaps XMMWORD PTR [rax+rsi*1],xmm0
    2792:	48 83 c1 02          	add    rcx,0x2
    2796:	48 83 c6 20          	add    rsi,0x20
    279a:	48 39 ca             	cmp    rdx,rcx
    279d:	75 e1                	jne    2780 <mesh_load_from_data+0x50>
    279f:	41 f6 c7 01          	test   r15b,0x1
    27a3:	74 0c                	je     27b1 <mesh_load_from_data+0x81>
    27a5:	48 c1 e1 04          	shl    rcx,0x4
    27a9:	0f 28 04 0b          	movaps xmm0,XMMWORD PTR [rbx+rcx*1]
    27ad:	0f 29 04 08          	movaps XMMWORD PTR [rax+rcx*1],xmm0
    27b1:	4c 89 f0             	mov    rax,r14
    27b4:	5b                   	pop    rbx
    27b5:	41 5e                	pop    r14
    27b7:	41 5f                	pop    r15
    27b9:	c3                   	ret
    27ba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000000027c0 <mesh_destroy>:
    27c0:	53                   	push   rbx
    27c1:	48 89 fb             	mov    rbx,rdi
    27c4:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    27c7:	e8 84 f9 ff ff       	call   2150 <free@plt>
    27cc:	48 89 df             	mov    rdi,rbx
    27cf:	5b                   	pop    rbx
    27d0:	e9 7b f9 ff ff       	jmp    2150 <free@plt>
    27d5:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    27dc:	00 00 00 
    27df:	90                   	nop

00000000000027e0 <r3d_draw_scene>:
    27e0:	55                   	push   rbp
    27e1:	41 57                	push   r15
    27e3:	41 56                	push   r14
    27e5:	53                   	push   rbx
    27e6:	48 83 ec 78          	sub    rsp,0x78
    27ea:	48 89 fb             	mov    rbx,rdi
    27ed:	8b 7f 18             	mov    edi,DWORD PTR [rdi+0x18]
    27f0:	8b 43 10             	mov    eax,DWORD PTR [rbx+0x10]
    27f3:	8b 4b 14             	mov    ecx,DWORD PTR [rbx+0x14]
    27f6:	99                   	cdq
    27f7:	f7 ff                	idiv   edi
    27f9:	89 c5                	mov    ebp,eax
    27fb:	89 c8                	mov    eax,ecx
    27fd:	99                   	cdq
    27fe:	f7 ff                	idiv   edi
    2800:	41 89 c6             	mov    r14d,eax
    2803:	f3 0f 10 43 1c       	movss  xmm0,DWORD PTR [rbx+0x1c]
    2808:	f3 0f 5a c0          	cvtss2sd xmm0,xmm0
    280c:	f2 0f 59 05 14 18 00 	mulsd  xmm0,QWORD PTR [rip+0x1814]        # 4028 <_IO_stdin_used+0x28>
    2813:	00 
    2814:	f2 0f 59 05 14 18 00 	mulsd  xmm0,QWORD PTR [rip+0x1814]        # 4030 <_IO_stdin_used+0x30>
    281b:	00 
    281c:	49 89 f7             	mov    r15,rsi
    281f:	f2 0f 5e 05 11 18 00 	divsd  xmm0,QWORD PTR [rip+0x1811]        # 4038 <_IO_stdin_used+0x38>
    2826:	00 
    2827:	e8 34 f8 ff ff       	call   2060 <tan@plt>
    282c:	85 ed                	test   ebp,ebp
    282e:	0f 8e 7b 03 00 00    	jle    2baf <r3d_draw_scene+0x3cf>
    2834:	f3 0f 2a 4b 10       	cvtsi2ss xmm1,DWORD PTR [rbx+0x10]
    2839:	f3 0f 2a 53 14       	cvtsi2ss xmm2,DWORD PTR [rbx+0x14]
    283e:	f3 0f 5e ca          	divss  xmm1,xmm2
    2842:	f2 0f 5a c0          	cvtsd2ss xmm0,xmm0
    2846:	0f 57 d2             	xorps  xmm2,xmm2
    2849:	f3 0f 2a d5          	cvtsi2ss xmm2,ebp
    284d:	f3 0f 5a d2          	cvtss2sd xmm2,xmm2
    2851:	f2 0f 11 54 24 20    	movsd  QWORD PTR [rsp+0x20],xmm2
    2857:	f3 0f 5a c9          	cvtss2sd xmm1,xmm1
    285b:	f2 0f 11 4c 24 18    	movsd  QWORD PTR [rsp+0x18],xmm1
    2861:	0f 57 c9             	xorps  xmm1,xmm1
    2864:	f3 41 0f 2a ce       	cvtsi2ss xmm1,r14d
    2869:	f3 0f 5a c0          	cvtss2sd xmm0,xmm0
    286d:	f2 0f 11 44 24 10    	movsd  QWORD PTR [rsp+0x10],xmm0
    2873:	0f 57 c0             	xorps  xmm0,xmm0
    2876:	f3 0f 5a c1          	cvtss2sd xmm0,xmm1
    287a:	f2 0f 11 44 24 30    	movsd  QWORD PTR [rsp+0x30],xmm0
    2880:	31 c0                	xor    eax,eax
    2882:	0f 57 c0             	xorps  xmm0,xmm0
    2885:	eb 21                	jmp    28a8 <r3d_draw_scene+0xc8>
    2887:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    288e:	00 00 
    2890:	f2 0f 10 44 24 28    	movsd  xmm0,QWORD PTR [rsp+0x28]
    2896:	f2 0f 58 05 aa 17 00 	addsd  xmm0,QWORD PTR [rip+0x17aa]        # 4048 <_IO_stdin_used+0x48>
    289d:	00 
    289e:	ff c0                	inc    eax
    28a0:	39 e8                	cmp    eax,ebp
    28a2:	0f 84 07 03 00 00    	je     2baf <r3d_draw_scene+0x3cf>
    28a8:	f2 0f 11 44 24 28    	movsd  QWORD PTR [rsp+0x28],xmm0
    28ae:	f2 0f 58 05 72 17 00 	addsd  xmm0,QWORD PTR [rip+0x1772]        # 4028 <_IO_stdin_used+0x28>
    28b5:	00 
    28b6:	f2 0f 5e 44 24 20    	divsd  xmm0,QWORD PTR [rsp+0x20]
    28bc:	f2 0f 58 c0          	addsd  xmm0,xmm0
    28c0:	f2 0f 58 05 78 17 00 	addsd  xmm0,QWORD PTR [rip+0x1778]        # 4040 <_IO_stdin_used+0x40>
    28c7:	00 
    28c8:	45 85 f6             	test   r14d,r14d
    28cb:	7e c3                	jle    2890 <r3d_draw_scene+0xb0>
    28cd:	f2 0f 59 44 24 18    	mulsd  xmm0,QWORD PTR [rsp+0x18]
    28d3:	f2 0f 59 44 24 10    	mulsd  xmm0,QWORD PTR [rsp+0x10]
    28d9:	f2 0f 5a c0          	cvtsd2ss xmm0,xmm0
    28dd:	49 8b 4f 08          	mov    rcx,QWORD PTR [r15+0x8]
    28e1:	0f 29 44 24 40       	movaps XMMWORD PTR [rsp+0x40],xmm0
    28e6:	0f 57 05 83 18 00 00 	xorps  xmm0,XMMWORD PTR [rip+0x1883]        # 4170 <_IO_stdin_used+0x170>
    28ed:	0f 29 44 24 60       	movaps XMMWORD PTR [rsp+0x60],xmm0
    28f2:	31 d2                	xor    edx,edx
    28f4:	0f 57 c0             	xorps  xmm0,xmm0
    28f7:	eb 20                	jmp    2919 <r3d_draw_scene+0x139>
    28f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2900:	f2 0f 10 44 24 38    	movsd  xmm0,QWORD PTR [rsp+0x38]
    2906:	f2 0f 58 05 3a 17 00 	addsd  xmm0,QWORD PTR [rip+0x173a]        # 4048 <_IO_stdin_used+0x48>
    290d:	00 
    290e:	ff c2                	inc    edx
    2910:	44 39 f2             	cmp    edx,r14d
    2913:	0f 84 77 ff ff ff    	je     2890 <r3d_draw_scene+0xb0>
    2919:	f2 0f 11 44 24 38    	movsd  QWORD PTR [rsp+0x38],xmm0
    291f:	f2 0f 58 05 01 17 00 	addsd  xmm0,QWORD PTR [rip+0x1701]        # 4028 <_IO_stdin_used+0x28>
    2926:	00 
    2927:	48 85 c9             	test   rcx,rcx
    292a:	74 d4                	je     2900 <r3d_draw_scene+0x120>
    292c:	f3 0f 10 4b 28       	movss  xmm1,DWORD PTR [rbx+0x28]
    2931:	f3 0f 11 4c 24 0c    	movss  DWORD PTR [rsp+0xc],xmm1
    2937:	f2 0f 5e 44 24 30    	divsd  xmm0,QWORD PTR [rsp+0x30]
    293d:	f2 0f 58 c0          	addsd  xmm0,xmm0
    2941:	f2 0f 10 0d ff 16 00 	movsd  xmm1,QWORD PTR [rip+0x16ff]        # 4048 <_IO_stdin_used+0x48>
    2948:	00 
    2949:	f2 0f 5c c8          	subsd  xmm1,xmm0
    294d:	f2 0f 59 4c 24 10    	mulsd  xmm1,QWORD PTR [rsp+0x10]
    2953:	f2 0f 5a f9          	cvtsd2ss xmm7,xmm1
    2957:	f2 0f 10 43 20       	movsd  xmm0,QWORD PTR [rbx+0x20]
    295c:	0f 29 44 24 50       	movaps XMMWORD PTR [rsp+0x50],xmm0
    2961:	49 8b 37             	mov    rsi,QWORD PTR [r15]
    2964:	44 0f 28 cf          	movaps xmm9,xmm7
    2968:	44 0f 57 0d 00 18 00 	xorps  xmm9,XMMWORD PTR [rip+0x1800]        # 4170 <_IO_stdin_used+0x170>
    296f:	00 
    2970:	48 83 c6 28          	add    rsi,0x28
    2974:	31 ff                	xor    edi,edi
    2976:	eb 19                	jmp    2991 <r3d_draw_scene+0x1b1>
    2978:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    297f:	00 
    2980:	48 83 c7 03          	add    rdi,0x3
    2984:	48 83 c6 30          	add    rsi,0x30
    2988:	48 39 cf             	cmp    rdi,rcx
    298b:	0f 83 6f ff ff ff    	jae    2900 <r3d_draw_scene+0x120>
    2991:	f2 0f 10 76 d8       	movsd  xmm6,QWORD PTR [rsi-0x28]
    2996:	f3 44 0f 10 7e e0    	movss  xmm15,DWORD PTR [rsi-0x20]
    299c:	f2 0f 10 56 e8       	movsd  xmm2,QWORD PTR [rsi-0x18]
    29a1:	f3 44 0f 10 46 f0    	movss  xmm8,DWORD PTR [rsi-0x10]
    29a7:	f2 0f 10 6e f8       	movsd  xmm5,QWORD PTR [rsi-0x8]
    29ac:	f3 44 0f 10 16       	movss  xmm10,DWORD PTR [rsi]
    29b1:	0f 5c d6             	subps  xmm2,xmm6
    29b4:	44 0f 28 e2          	movaps xmm12,xmm2
    29b8:	44 0f c6 e2 55       	shufps xmm12,xmm2,0x55
    29bd:	f3 45 0f 5c c7       	subss  xmm8,xmm15
    29c2:	0f 5c ee             	subps  xmm5,xmm6
    29c5:	0f 28 dd             	movaps xmm3,xmm5
    29c8:	0f c6 dd 55          	shufps xmm3,xmm5,0x55
    29cc:	f3 45 0f 5c d7       	subss  xmm10,xmm15
    29d1:	0f 28 cf             	movaps xmm1,xmm7
    29d4:	f3 41 0f 59 ca       	mulss  xmm1,xmm10
    29d9:	f3 0f 58 cb          	addss  xmm1,xmm3
    29dd:	41 0f 28 e2          	movaps xmm4,xmm10
    29e1:	f3 0f 59 64 24 60    	mulss  xmm4,DWORD PTR [rsp+0x60]
    29e7:	f3 0f 5c e5          	subss  xmm4,xmm5
    29eb:	0f 28 c5             	movaps xmm0,xmm5
    29ee:	f3 41 0f 59 c1       	mulss  xmm0,xmm9
    29f3:	44 0f 28 6c 24 40    	movaps xmm13,XMMWORD PTR [rsp+0x40]
    29f9:	f3 44 0f 59 eb       	mulss  xmm13,xmm3
    29fe:	f3 44 0f 58 e8       	addss  xmm13,xmm0
    2a03:	41 0f 28 c4          	movaps xmm0,xmm12
    2a07:	f3 0f 59 c4          	mulss  xmm0,xmm4
    2a0b:	44 0f 28 da          	movaps xmm11,xmm2
    2a0f:	f3 44 0f 59 d9       	mulss  xmm11,xmm1
    2a14:	f3 44 0f 58 d8       	addss  xmm11,xmm0
    2a19:	41 0f 28 c0          	movaps xmm0,xmm8
    2a1d:	f3 41 0f 59 c5       	mulss  xmm0,xmm13
    2a22:	f3 41 0f 58 c3       	addss  xmm0,xmm11
    2a27:	45 0f 57 db          	xorps  xmm11,xmm11
    2a2b:	f3 44 0f 5a d8       	cvtss2sd xmm11,xmm0
    2a30:	66 44 0f 2e 1d 17 16 	ucomisd xmm11,QWORD PTR [rip+0x1617]        # 4050 <_IO_stdin_used+0x50>
    2a37:	00 00 
    2a39:	76 0f                	jbe    2a4a <r3d_draw_scene+0x26a>
    2a3b:	66 44 0f 2e 1d 14 16 	ucomisd xmm11,QWORD PTR [rip+0x1614]        # 4058 <_IO_stdin_used+0x58>
    2a42:	00 00 
    2a44:	0f 82 36 ff ff ff    	jb     2980 <r3d_draw_scene+0x1a0>
    2a4a:	f3 44 0f 10 1d b5 15 	movss  xmm11,DWORD PTR [rip+0x15b5]        # 4008 <_IO_stdin_used+0x8>
    2a51:	00 00 
    2a53:	f3 44 0f 5e d8       	divss  xmm11,xmm0
    2a58:	0f 28 44 24 50       	movaps xmm0,XMMWORD PTR [rsp+0x50]
    2a5d:	0f 5c c6             	subps  xmm0,xmm6
    2a60:	44 0f 28 f0          	movaps xmm14,xmm0
    2a64:	44 0f c6 f0 55       	shufps xmm14,xmm0,0x55
    2a69:	f3 0f 10 74 24 0c    	movss  xmm6,DWORD PTR [rsp+0xc]
    2a6f:	f3 41 0f 5c f7       	subss  xmm6,xmm15
    2a74:	f3 41 0f 59 e6       	mulss  xmm4,xmm14
    2a79:	f3 0f 59 c8          	mulss  xmm1,xmm0
    2a7d:	f3 0f 58 cc          	addss  xmm1,xmm4
    2a81:	f3 44 0f 59 ee       	mulss  xmm13,xmm6
    2a86:	f3 44 0f 58 e9       	addss  xmm13,xmm1
    2a8b:	f3 45 0f 59 eb       	mulss  xmm13,xmm11
    2a90:	44 0f 2e 2d 74 15 00 	ucomiss xmm13,DWORD PTR [rip+0x1574]        # 400c <_IO_stdin_used+0xc>
    2a97:	00 
    2a98:	0f 82 e2 fe ff ff    	jb     2980 <r3d_draw_scene+0x1a0>
    2a9e:	44 0f 2e 2d 62 15 00 	ucomiss xmm13,DWORD PTR [rip+0x1562]        # 4008 <_IO_stdin_used+0x8>
    2aa5:	00 
    2aa6:	0f 87 d4 fe ff ff    	ja     2980 <r3d_draw_scene+0x1a0>
    2aac:	0f 28 e6             	movaps xmm4,xmm6
    2aaf:	f3 41 0f 59 e4       	mulss  xmm4,xmm12
    2ab4:	41 0f 28 ce          	movaps xmm1,xmm14
    2ab8:	f3 41 0f 59 c8       	mulss  xmm1,xmm8
    2abd:	f3 0f 5c cc          	subss  xmm1,xmm4
    2ac1:	f3 44 0f 59 c0       	mulss  xmm8,xmm0
    2ac6:	f3 0f 59 f2          	mulss  xmm6,xmm2
    2aca:	f3 41 0f 5c f0       	subss  xmm6,xmm8
    2acf:	f3 41 0f 59 d6       	mulss  xmm2,xmm14
    2ad4:	f3 41 0f 59 c4       	mulss  xmm0,xmm12
    2ad9:	f3 0f 5c c2          	subss  xmm0,xmm2
    2add:	0f 28 e6             	movaps xmm4,xmm6
    2ae0:	f3 0f 59 e7          	mulss  xmm4,xmm7
    2ae4:	0f 28 54 24 40       	movaps xmm2,XMMWORD PTR [rsp+0x40]
    2ae9:	f3 0f 59 d1          	mulss  xmm2,xmm1
    2aed:	f3 0f 58 d4          	addss  xmm2,xmm4
    2af1:	f3 0f 5c d0          	subss  xmm2,xmm0
    2af5:	f3 41 0f 59 d3       	mulss  xmm2,xmm11
    2afa:	0f 2e 15 0b 15 00 00 	ucomiss xmm2,DWORD PTR [rip+0x150b]        # 400c <_IO_stdin_used+0xc>
    2b01:	0f 82 79 fe ff ff    	jb     2980 <r3d_draw_scene+0x1a0>
    2b07:	f3 44 0f 58 ea       	addss  xmm13,xmm2
    2b0c:	44 0f 2e 2d f4 14 00 	ucomiss xmm13,DWORD PTR [rip+0x14f4]        # 4008 <_IO_stdin_used+0x8>
    2b13:	00 
    2b14:	0f 87 66 fe ff ff    	ja     2980 <r3d_draw_scene+0x1a0>
    2b1a:	f3 0f 59 de          	mulss  xmm3,xmm6
    2b1e:	f3 0f 59 e9          	mulss  xmm5,xmm1
    2b22:	f3 0f 58 eb          	addss  xmm5,xmm3
    2b26:	f3 44 0f 59 d0       	mulss  xmm10,xmm0
    2b2b:	f3 44 0f 58 d5       	addss  xmm10,xmm5
    2b30:	f3 45 0f 59 d3       	mulss  xmm10,xmm11
    2b35:	0f 57 c0             	xorps  xmm0,xmm0
    2b38:	f3 41 0f 5a c2       	cvtss2sd xmm0,xmm10
    2b3d:	66 0f 2e 05 13 15 00 	ucomisd xmm0,QWORD PTR [rip+0x1513]        # 4058 <_IO_stdin_used+0x58>
    2b44:	00 
    2b45:	0f 86 35 fe ff ff    	jbe    2980 <r3d_draw_scene+0x1a0>
    2b4b:	8b 7b 18             	mov    edi,DWORD PTR [rbx+0x18]
    2b4e:	85 ff                	test   edi,edi
    2b50:	0f 8e aa fd ff ff    	jle    2900 <r3d_draw_scene+0x120>
    2b56:	31 f6                	xor    esi,esi
    2b58:	eb 10                	jmp    2b6a <r3d_draw_scene+0x38a>
    2b5a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2b60:	ff c6                	inc    esi
    2b62:	39 fe                	cmp    esi,edi
    2b64:	0f 8d 96 fd ff ff    	jge    2900 <r3d_draw_scene+0x120>
    2b6a:	85 ff                	test   edi,edi
    2b6c:	7e f2                	jle    2b60 <r3d_draw_scene+0x380>
    2b6e:	4c 8b 43 08          	mov    r8,QWORD PTR [rbx+0x8]
    2b72:	45 31 c9             	xor    r9d,r9d
    2b75:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    2b7c:	00 00 00 00 
    2b80:	41 89 d2             	mov    r10d,edx
    2b83:	44 0f af d7          	imul   r10d,edi
    2b87:	0f af f8             	imul   edi,eax
    2b8a:	01 f7                	add    edi,esi
    2b8c:	45 01 ca             	add    r10d,r9d
    2b8f:	44 0f af 53 10       	imul   r10d,DWORD PTR [rbx+0x10]
    2b94:	41 01 fa             	add    r10d,edi
    2b97:	49 63 fa             	movsxd rdi,r10d
    2b9a:	41 c7 04 b8 ff ff ff 	mov    DWORD PTR [r8+rdi*4],0xffffffff
    2ba1:	ff 
    2ba2:	41 ff c1             	inc    r9d
    2ba5:	8b 7b 18             	mov    edi,DWORD PTR [rbx+0x18]
    2ba8:	41 39 f9             	cmp    r9d,edi
    2bab:	7c d3                	jl     2b80 <r3d_draw_scene+0x3a0>
    2bad:	eb b1                	jmp    2b60 <r3d_draw_scene+0x380>
    2baf:	48 83 c4 78          	add    rsp,0x78
    2bb3:	5b                   	pop    rbx
    2bb4:	41 5e                	pop    r14
    2bb6:	41 5f                	pop    r15
    2bb8:	5d                   	pop    rbp
    2bb9:	c3                   	ret
    2bba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000002bc0 <mlx_int_deal_shm>:
    2bc0:	41 54                	push   r12
    2bc2:	55                   	push   rbp
    2bc3:	53                   	push   rbx
    2bc4:	48 89 fb             	mov    rbx,rdi
    2bc7:	48 83 ec 40          	sub    rsp,0x40
    2bcb:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    2bce:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2bd5:	00 00 
    2bd7:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
    2bdc:	31 c0                	xor    eax,eax
    2bde:	48 8d 74 24 0c       	lea    rsi,[rsp+0xc]
    2be3:	48 8d 4c 24 08       	lea    rcx,[rsp+0x8]
    2be8:	48 89 f2             	mov    rdx,rsi
    2beb:	e8 d0 f5 ff ff       	call   21c0 <XShmQueryVersion@plt>
    2bf0:	ba ff ff ff ff       	mov    edx,0xffffffff
    2bf5:	89 43 48             	mov    DWORD PTR [rbx+0x48],eax
    2bf8:	85 c0                	test   eax,eax
    2bfa:	74 0c                	je     2c08 <mlx_int_deal_shm+0x48>
    2bfc:	8b 44 24 08          	mov    eax,DWORD PTR [rsp+0x8]
    2c00:	85 c0                	test   eax,eax
    2c02:	0f 85 98 00 00 00    	jne    2ca0 <mlx_int_deal_shm+0xe0>
    2c08:	89 53 4c             	mov    DWORD PTR [rbx+0x4c],edx
    2c0b:	4c 8d 64 24 10       	lea    r12,[rsp+0x10]
    2c10:	be 20 00 00 00       	mov    esi,0x20
    2c15:	4c 89 e7             	mov    rdi,r12
    2c18:	e8 e3 f5 ff ff       	call   2200 <gethostname@plt>
    2c1d:	48 8d 3d 0d 15 00 00 	lea    rdi,[rip+0x150d]        # 4131 <_IO_stdin_used+0x131>
    2c24:	e8 07 f6 ff ff       	call   2230 <getenv@plt>
    2c29:	48 89 c5             	mov    rbp,rax
    2c2c:	48 85 c0             	test   rax,rax
    2c2f:	74 4f                	je     2c80 <mlx_int_deal_shm+0xc0>
    2c31:	0f b6 00             	movzx  eax,BYTE PTR [rax]
    2c34:	3c 3a                	cmp    al,0x3a
    2c36:	74 48                	je     2c80 <mlx_int_deal_shm+0xc0>
    2c38:	84 c0                	test   al,al
    2c3a:	74 44                	je     2c80 <mlx_int_deal_shm+0xc0>
    2c3c:	4c 89 e7             	mov    rdi,r12
    2c3f:	e8 2c f5 ff ff       	call   2170 <strlen@plt>
    2c44:	4c 89 e6             	mov    rsi,r12
    2c47:	48 89 ef             	mov    rdi,rbp
    2c4a:	48 89 c2             	mov    rdx,rax
    2c4d:	e8 7e f4 ff ff       	call   20d0 <strncmp@plt>
    2c52:	85 c0                	test   eax,eax
    2c54:	74 2a                	je     2c80 <mlx_int_deal_shm+0xc0>
    2c56:	ba 09 00 00 00       	mov    edx,0x9
    2c5b:	48 8d 35 d7 14 00 00 	lea    rsi,[rip+0x14d7]        # 4139 <_IO_stdin_used+0x139>
    2c62:	48 89 ef             	mov    rdi,rbp
    2c65:	e8 66 f4 ff ff       	call   20d0 <strncmp@plt>
    2c6a:	85 c0                	test   eax,eax
    2c6c:	74 12                	je     2c80 <mlx_int_deal_shm+0xc0>
    2c6e:	48 8b 05 eb 13 00 00 	mov    rax,QWORD PTR [rip+0x13eb]        # 4060 <_IO_stdin_used+0x60>
    2c75:	48 89 43 48          	mov    QWORD PTR [rbx+0x48],rax
    2c79:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2c80:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
    2c85:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    2c8c:	00 00 
    2c8e:	75 1f                	jne    2caf <mlx_int_deal_shm+0xef>
    2c90:	48 83 c4 40          	add    rsp,0x40
    2c94:	31 c0                	xor    eax,eax
    2c96:	5b                   	pop    rbx
    2c97:	5d                   	pop    rbp
    2c98:	41 5c                	pop    r12
    2c9a:	c3                   	ret
    2c9b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    2ca0:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2ca3:	e8 88 f6 ff ff       	call   2330 <XShmPixmapFormat@plt>
    2ca8:	89 c2                	mov    edx,eax
    2caa:	e9 59 ff ff ff       	jmp    2c08 <mlx_int_deal_shm+0x48>
    2caf:	e8 bc f5 ff ff       	call   2270 <__stack_chk_fail@plt>
    2cb4:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    2cbb:	00 00 00 00 
    2cbf:	90                   	nop

0000000000002cc0 <mlx_int_rgb_conversion>:
    2cc0:	48 8b 77 18          	mov    rsi,QWORD PTR [rdi+0x18]
    2cc4:	66 0f ef c0          	pxor   xmm0,xmm0
    2cc8:	48 c7 47 64 00 00 00 	mov    QWORD PTR [rdi+0x64],0x0
    2ccf:	00 
    2cd0:	0f 11 47 54          	movups XMMWORD PTR [rdi+0x54],xmm0
    2cd4:	48 8b 46 18          	mov    rax,QWORD PTR [rsi+0x18]
    2cd8:	a8 01                	test   al,0x1
    2cda:	75 1b                	jne    2cf7 <mlx_int_rgb_conversion+0x37>
    2cdc:	ba 01 00 00 00       	mov    edx,0x1
    2ce1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2ce8:	48 d1 e8             	shr    rax,1
    2ceb:	89 d1                	mov    ecx,edx
    2ced:	83 c2 01             	add    edx,0x1
    2cf0:	a8 01                	test   al,0x1
    2cf2:	74 f4                	je     2ce8 <mlx_int_rgb_conversion+0x28>
    2cf4:	89 4f 54             	mov    DWORD PTR [rdi+0x54],ecx
    2cf7:	ba 01 00 00 00       	mov    edx,0x1
    2cfc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    2d00:	48 d1 e8             	shr    rax,1
    2d03:	89 d1                	mov    ecx,edx
    2d05:	83 c2 01             	add    edx,0x1
    2d08:	a8 01                	test   al,0x1
    2d0a:	75 f4                	jne    2d00 <mlx_int_rgb_conversion+0x40>
    2d0c:	48 89 46 18          	mov    QWORD PTR [rsi+0x18],rax
    2d10:	48 8b 46 20          	mov    rax,QWORD PTR [rsi+0x20]
    2d14:	89 4f 58             	mov    DWORD PTR [rdi+0x58],ecx
    2d17:	a8 01                	test   al,0x1
    2d19:	75 12                	jne    2d2d <mlx_int_rgb_conversion+0x6d>
    2d1b:	31 d2                	xor    edx,edx
    2d1d:	0f 1f 00             	nop    DWORD PTR [rax]
    2d20:	48 d1 e8             	shr    rax,1
    2d23:	83 c2 01             	add    edx,0x1
    2d26:	a8 01                	test   al,0x1
    2d28:	74 f6                	je     2d20 <mlx_int_rgb_conversion+0x60>
    2d2a:	89 57 5c             	mov    DWORD PTR [rdi+0x5c],edx
    2d2d:	ba 01 00 00 00       	mov    edx,0x1
    2d32:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2d38:	48 d1 e8             	shr    rax,1
    2d3b:	89 d1                	mov    ecx,edx
    2d3d:	83 c2 01             	add    edx,0x1
    2d40:	a8 01                	test   al,0x1
    2d42:	75 f4                	jne    2d38 <mlx_int_rgb_conversion+0x78>
    2d44:	48 89 46 20          	mov    QWORD PTR [rsi+0x20],rax
    2d48:	48 8b 46 28          	mov    rax,QWORD PTR [rsi+0x28]
    2d4c:	89 4f 60             	mov    DWORD PTR [rdi+0x60],ecx
    2d4f:	a8 01                	test   al,0x1
    2d51:	75 12                	jne    2d65 <mlx_int_rgb_conversion+0xa5>
    2d53:	31 d2                	xor    edx,edx
    2d55:	0f 1f 00             	nop    DWORD PTR [rax]
    2d58:	48 d1 e8             	shr    rax,1
    2d5b:	83 c2 01             	add    edx,0x1
    2d5e:	a8 01                	test   al,0x1
    2d60:	74 f6                	je     2d58 <mlx_int_rgb_conversion+0x98>
    2d62:	89 57 64             	mov    DWORD PTR [rdi+0x64],edx
    2d65:	ba 01 00 00 00       	mov    edx,0x1
    2d6a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2d70:	48 d1 e8             	shr    rax,1
    2d73:	89 d1                	mov    ecx,edx
    2d75:	83 c2 01             	add    edx,0x1
    2d78:	a8 01                	test   al,0x1
    2d7a:	75 f4                	jne    2d70 <mlx_int_rgb_conversion+0xb0>
    2d7c:	48 89 46 28          	mov    QWORD PTR [rsi+0x28],rax
    2d80:	89 4f 68             	mov    DWORD PTR [rdi+0x68],ecx
    2d83:	c3                   	ret
    2d84:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    2d8b:	00 00 00 00 
    2d8f:	90                   	nop

0000000000002d90 <mlx_init>:
    2d90:	53                   	push   rbx
    2d91:	bf 88 00 00 00       	mov    edi,0x88
    2d96:	e8 45 f3 ff ff       	call   20e0 <malloc@plt>
    2d9b:	48 85 c0             	test   rax,rax
    2d9e:	0f 84 04 01 00 00    	je     2ea8 <mlx_init+0x118>
    2da4:	48 8d 3d 76 13 00 00 	lea    rdi,[rip+0x1376]        # 4121 <_IO_stdin_used+0x121>
    2dab:	48 89 c3             	mov    rbx,rax
    2dae:	e8 8d f3 ff ff       	call   2140 <XOpenDisplay@plt>
    2db3:	48 89 03             	mov    QWORD PTR [rbx],rax
    2db6:	48 89 c2             	mov    rdx,rax
    2db9:	48 85 c0             	test   rax,rax
    2dbc:	0f 84 de 00 00 00    	je     2ea0 <mlx_init+0x110>
    2dc2:	48 63 80 e0 00 00 00 	movsxd rax,DWORD PTR [rax+0xe0]
    2dc9:	48 89 df             	mov    rdi,rbx
    2dcc:	48 89 c1             	mov    rcx,rax
    2dcf:	48 c1 e0 07          	shl    rax,0x7
    2dd3:	48 03 82 e8 00 00 00 	add    rax,QWORD PTR [rdx+0xe8]
    2dda:	48 8b 50 10          	mov    rdx,QWORD PTR [rax+0x10]
    2dde:	66 0f 6e 40 38       	movd   xmm0,DWORD PTR [rax+0x38]
    2de3:	66 0f 6e c9          	movd   xmm1,ecx
    2de7:	48 89 53 08          	mov    QWORD PTR [rbx+0x8],rdx
    2deb:	48 8b 50 50          	mov    rdx,QWORD PTR [rax+0x50]
    2def:	66 0f 62 c8          	punpckldq xmm1,xmm0
    2df3:	66 0f d6 4b 10       	movq   QWORD PTR [rbx+0x10],xmm1
    2df8:	48 89 53 20          	mov    QWORD PTR [rbx+0x20],rdx
    2dfc:	e8 df 04 00 00       	call   32e0 <mlx_int_get_visual>
    2e01:	83 f8 ff             	cmp    eax,0xffffffff
    2e04:	0f 84 a2 00 00 00    	je     2eac <mlx_init+0x11c>
    2e0a:	48 c7 43 30 00 00 00 	mov    QWORD PTR [rbx+0x30],0x0
    2e11:	00 
    2e12:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2e15:	31 d2                	xor    edx,edx
    2e17:	48 8d 35 25 13 00 00 	lea    rsi,[rip+0x1325]        # 4143 <_IO_stdin_used+0x143>
    2e1e:	48 c7 43 38 00 00 00 	mov    QWORD PTR [rbx+0x38],0x0
    2e25:	00 
    2e26:	48 c7 43 40 00 00 00 	mov    QWORD PTR [rbx+0x40],0x0
    2e2d:	00 
    2e2e:	c7 43 50 01 00 00 00 	mov    DWORD PTR [rbx+0x50],0x1
    2e35:	e8 86 f4 ff ff       	call   22c0 <XInternAtom@plt>
    2e3a:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2e3d:	31 d2                	xor    edx,edx
    2e3f:	48 8d 35 0e 13 00 00 	lea    rsi,[rip+0x130e]        # 4154 <_IO_stdin_used+0x154>
    2e46:	48 89 43 70          	mov    QWORD PTR [rbx+0x70],rax
    2e4a:	e8 71 f4 ff ff       	call   22c0 <XInternAtom@plt>
    2e4f:	48 89 df             	mov    rdi,rbx
    2e52:	48 89 43 78          	mov    QWORD PTR [rbx+0x78],rax
    2e56:	31 c0                	xor    eax,eax
    2e58:	e8 63 fd ff ff       	call   2bc0 <mlx_int_deal_shm>
    2e5d:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    2e60:	85 c0                	test   eax,eax
    2e62:	75 1c                	jne    2e80 <mlx_init+0xf0>
    2e64:	48 89 df             	mov    rdi,rbx
    2e67:	31 c0                	xor    eax,eax
    2e69:	e8 52 fe ff ff       	call   2cc0 <mlx_int_rgb_conversion>
    2e6e:	c7 83 80 00 00 00 00 	mov    DWORD PTR [rbx+0x80],0x0
    2e75:	00 00 00 
    2e78:	48 89 d8             	mov    rax,rbx
    2e7b:	5b                   	pop    rbx
    2e7c:	c3                   	ret
    2e7d:	0f 1f 00             	nop    DWORD PTR [rax]
    2e80:	48 8b 53 18          	mov    rdx,QWORD PTR [rbx+0x18]
    2e84:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    2e88:	31 c9                	xor    ecx,ecx
    2e8a:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2e8d:	e8 8e f2 ff ff       	call   2120 <XCreateColormap@plt>
    2e92:	48 89 43 20          	mov    QWORD PTR [rbx+0x20],rax
    2e96:	eb cc                	jmp    2e64 <mlx_init+0xd4>
    2e98:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    2e9f:	00 
    2ea0:	48 89 df             	mov    rdi,rbx
    2ea3:	e8 a8 f2 ff ff       	call   2150 <free@plt>
    2ea8:	31 db                	xor    ebx,ebx
    2eaa:	eb cc                	jmp    2e78 <mlx_init+0xe8>
    2eac:	48 8d 3d cd 12 00 00 	lea    rdi,[rip+0x12cd]        # 4180 <_IO_stdin_used+0x180>
    2eb3:	e8 c8 f1 ff ff       	call   2080 <puts@plt>
    2eb8:	bf 01 00 00 00       	mov    edi,0x1
    2ebd:	e8 de f1 ff ff       	call   20a0 <exit@plt>
    2ec2:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    2ec9:	00 00 00 
    2ecc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000002ed0 <mlx_new_window>:
    2ed0:	41 56                	push   r14
    2ed2:	49 89 ce             	mov    r14,rcx
    2ed5:	41 55                	push   r13
    2ed7:	41 89 d5             	mov    r13d,edx
    2eda:	41 54                	push   r12
    2edc:	41 89 f4             	mov    r12d,esi
    2edf:	55                   	push   rbp
    2ee0:	53                   	push   rbx
    2ee1:	48 89 fb             	mov    rbx,rdi
    2ee4:	48 81 ec 00 01 00 00 	sub    rsp,0x100
    2eeb:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2ef2:	00 00 
    2ef4:	48 89 84 24 f8 00 00 	mov    QWORD PTR [rsp+0xf8],rax
    2efb:	00 
    2efc:	31 c0                	xor    eax,eax
    2efe:	48 8b 47 20          	mov    rax,QWORD PTR [rdi+0x20]
    2f02:	bf a8 03 00 00       	mov    edi,0x3a8
    2f07:	48 c7 44 24 08 00 00 	mov    QWORD PTR [rsp+0x8],0x0
    2f0e:	00 00 
    2f10:	48 c7 44 24 18 ff ff 	mov    QWORD PTR [rsp+0x18],0xffffffffffffffff
    2f17:	ff ff 
    2f19:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
    2f1e:	48 c7 44 24 48 ff ff 	mov    QWORD PTR [rsp+0x48],0xffffff
    2f25:	ff 00 
    2f27:	e8 b4 f1 ff ff       	call   20e0 <malloc@plt>
    2f2c:	48 89 c5             	mov    rbp,rax
    2f2f:	48 85 c0             	test   rax,rax
    2f32:	0f 84 ca 00 00 00    	je     3002 <mlx_new_window+0x132>
    2f38:	48 89 e0             	mov    rax,rsp
    2f3b:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    2f3f:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2f42:	45 89 e9             	mov    r9d,r13d
    2f45:	50                   	push   rax
    2f46:	45 89 e0             	mov    r8d,r12d
    2f49:	31 c9                	xor    ecx,ecx
    2f4b:	31 d2                	xor    edx,edx
    2f4d:	68 0a 28 00 00       	push   0x280a
    2f52:	ff 73 18             	push   QWORD PTR [rbx+0x18]
    2f55:	6a 01                	push   0x1
    2f57:	6a 00                	push   0x0
    2f59:	6a 00                	push   0x0
    2f5b:	e8 a0 f1 ff ff       	call   2100 <XCreateWindow@plt>
    2f60:	48 83 c4 30          	add    rsp,0x30
    2f64:	44 89 e9             	mov    ecx,r13d
    2f67:	44 89 e2             	mov    edx,r12d
    2f6a:	48 89 45 00          	mov    QWORD PTR [rbp+0x0],rax
    2f6e:	48 89 c6             	mov    rsi,rax
    2f71:	48 89 df             	mov    rdi,rbx
    2f74:	31 c0                	xor    eax,eax
    2f76:	e8 35 02 00 00       	call   31b0 <mlx_int_anti_resize_win>
    2f7b:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2f7f:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2f82:	4c 89 f2             	mov    rdx,r14
    2f85:	e8 c6 f0 ff ff       	call   2050 <XStoreName@plt>
    2f8a:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2f8e:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2f91:	48 8d 53 70          	lea    rdx,[rbx+0x70]
    2f95:	b9 01 00 00 00       	mov    ecx,0x1
    2f9a:	e8 51 f2 ff ff       	call   21f0 <XSetWMProtocols@plt>
    2f9f:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2fa3:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2fa6:	66 0f 76 c0          	pcmpeqd xmm0,xmm0
    2faa:	48 8d 4c 24 70       	lea    rcx,[rsp+0x70]
    2faf:	ba 07 00 00 00       	mov    edx,0x7
    2fb4:	0f 11 44 24 78       	movups XMMWORD PTR [rsp+0x78],xmm0
    2fb9:	c7 44 24 70 03 00 00 	mov    DWORD PTR [rsp+0x70],0x3
    2fc0:	00 
    2fc1:	e8 5a f2 ff ff       	call   2220 <XCreateGC@plt>
    2fc6:	48 8d 55 48          	lea    rdx,[rbp+0x48]
    2fca:	b9 6c 00 00 00       	mov    ecx,0x6c
    2fcf:	66 48 0f 6e c0       	movq   xmm0,rax
    2fd4:	48 89 d7             	mov    rdi,rdx
    2fd7:	31 c0                	xor    eax,eax
    2fd9:	0f 16 43 30          	movhps xmm0,QWORD PTR [rbx+0x30]
    2fdd:	48 89 6b 30          	mov    QWORD PTR [rbx+0x30],rbp
    2fe1:	0f 11 45 08          	movups XMMWORD PTR [rbp+0x8],xmm0
    2fe5:	f3 48 ab             	rep stos QWORD PTR es:[rdi],rax
    2fe8:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2feb:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2fef:	e8 2c f3 ff ff       	call   2320 <XMapRaised@plt>
    2ff4:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2ff8:	48 89 df             	mov    rdi,rbx
    2ffb:	31 c0                	xor    eax,eax
    2ffd:	e8 6e 02 00 00       	call   3270 <mlx_int_wait_first_expose>
    3002:	48 8b 84 24 f8 00 00 	mov    rax,QWORD PTR [rsp+0xf8]
    3009:	00 
    300a:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3011:	00 00 
    3013:	75 13                	jne    3028 <mlx_new_window+0x158>
    3015:	48 81 c4 00 01 00 00 	add    rsp,0x100
    301c:	48 89 e8             	mov    rax,rbp
    301f:	5b                   	pop    rbx
    3020:	5d                   	pop    rbp
    3021:	41 5c                	pop    r12
    3023:	41 5d                	pop    r13
    3025:	41 5e                	pop    r14
    3027:	c3                   	ret
    3028:	e8 43 f2 ff ff       	call   2270 <__stack_chk_fail@plt>
    302d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000003030 <mlx_loop_end>:
    3030:	c7 87 80 00 00 00 01 	mov    DWORD PTR [rdi+0x80],0x1
    3037:	00 00 00 
    303a:	b8 01 00 00 00       	mov    eax,0x1
    303f:	c3                   	ret

0000000000003040 <mlx_loop>:
    3040:	41 54                	push   r12
    3042:	55                   	push   rbp
    3043:	53                   	push   rbx
    3044:	48 89 fb             	mov    rbx,rdi
    3047:	48 81 ec e0 00 00 00 	sub    rsp,0xe0
    304e:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    3055:	00 00 
    3057:	48 89 84 24 d8 00 00 	mov    QWORD PTR [rsp+0xd8],rax
    305e:	00 
    305f:	31 c0                	xor    eax,eax
    3061:	48 8d 6c 24 10       	lea    rbp,[rsp+0x10]
    3066:	e8 c5 0a 00 00       	call   3b30 <mlx_int_set_win_event_mask>
    306b:	c7 43 50 00 00 00 00 	mov    DWORD PTR [rbx+0x50],0x0
    3072:	4c 8d 25 67 31 00 00 	lea    r12,[rip+0x3167]        # 61e0 <mlx_int_param_event>
    3079:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    3080:	48 83 7b 30 00       	cmp    QWORD PTR [rbx+0x30],0x0
    3085:	0f 84 f2 00 00 00    	je     317d <mlx_loop+0x13d>
    308b:	8b 83 80 00 00 00    	mov    eax,DWORD PTR [rbx+0x80]
    3091:	85 c0                	test   eax,eax
    3093:	0f 85 e4 00 00 00    	jne    317d <mlx_loop+0x13d>
    3099:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    309c:	85 c0                	test   eax,eax
    309e:	75 59                	jne    30f9 <mlx_loop+0xb9>
    30a0:	48 83 7b 38 00       	cmp    QWORD PTR [rbx+0x38],0x0
    30a5:	74 0c                	je     30b3 <mlx_loop+0x73>
    30a7:	e8 c4 f2 ff ff       	call   2370 <XPending@plt>
    30ac:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    30af:	85 c0                	test   eax,eax
    30b1:	74 46                	je     30f9 <mlx_loop+0xb9>
    30b3:	48 89 ee             	mov    rsi,rbp
    30b6:	e8 15 f1 ff ff       	call   21d0 <XNextEvent@plt>
    30bb:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
    30bf:	48 85 d2             	test   rdx,rdx
    30c2:	74 28                	je     30ec <mlx_loop+0xac>
    30c4:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
    30c9:	eb 0e                	jmp    30d9 <mlx_loop+0x99>
    30cb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    30d0:	48 8b 52 10          	mov    rdx,QWORD PTR [rdx+0x10]
    30d4:	48 85 d2             	test   rdx,rdx
    30d7:	74 13                	je     30ec <mlx_loop+0xac>
    30d9:	48 39 02             	cmp    QWORD PTR [rdx],rax
    30dc:	75 f2                	jne    30d0 <mlx_loop+0x90>
    30de:	8b 44 24 10          	mov    eax,DWORD PTR [rsp+0x10]
    30e2:	83 f8 21             	cmp    eax,0x21
    30e5:	74 39                	je     3120 <mlx_loop+0xe0>
    30e7:	83 f8 23             	cmp    eax,0x23
    30ea:	7e 3f                	jle    312b <mlx_loop+0xeb>
    30ec:	8b 83 80 00 00 00    	mov    eax,DWORD PTR [rbx+0x80]
    30f2:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    30f5:	85 c0                	test   eax,eax
    30f7:	74 a7                	je     30a0 <mlx_loop+0x60>
    30f9:	31 f6                	xor    esi,esi
    30fb:	e8 60 f1 ff ff       	call   2260 <XSync@plt>
    3100:	48 8b 53 38          	mov    rdx,QWORD PTR [rbx+0x38]
    3104:	48 85 d2             	test   rdx,rdx
    3107:	0f 84 73 ff ff ff    	je     3080 <mlx_loop+0x40>
    310d:	48 8b 7b 40          	mov    rdi,QWORD PTR [rbx+0x40]
    3111:	31 c0                	xor    eax,eax
    3113:	ff d2                	call   rdx
    3115:	e9 58 ff ff ff       	jmp    3072 <mlx_loop+0x32>
    311a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3120:	48 8b 4b 78          	mov    rcx,QWORD PTR [rbx+0x78]
    3124:	48 39 4c 24 38       	cmp    QWORD PTR [rsp+0x38],rcx
    3129:	74 1d                	je     3148 <mlx_loop+0x108>
    312b:	48 63 c8             	movsxd rcx,eax
    312e:	48 8d 04 49          	lea    rax,[rcx+rcx*2]
    3132:	48 83 7c c2 50 00    	cmp    QWORD PTR [rdx+rax*8+0x50],0x0
    3138:	74 b2                	je     30ec <mlx_loop+0xac>
    313a:	48 89 ee             	mov    rsi,rbp
    313d:	48 89 df             	mov    rdi,rbx
    3140:	31 c0                	xor    eax,eax
    3142:	41 ff 14 cc          	call   QWORD PTR [r12+rcx*8]
    3146:	eb a4                	jmp    30ec <mlx_loop+0xac>
    3148:	48 8b 73 70          	mov    rsi,QWORD PTR [rbx+0x70]
    314c:	48 39 74 24 48       	cmp    QWORD PTR [rsp+0x48],rsi
    3151:	75 d8                	jne    312b <mlx_loop+0xeb>
    3153:	48 8b 8a e8 01 00 00 	mov    rcx,QWORD PTR [rdx+0x1e8]
    315a:	48 85 c9             	test   rcx,rcx
    315d:	74 cc                	je     312b <mlx_loop+0xeb>
    315f:	48 89 54 24 08       	mov    QWORD PTR [rsp+0x8],rdx
    3164:	48 8b ba f0 01 00 00 	mov    rdi,QWORD PTR [rdx+0x1f0]
    316b:	31 c0                	xor    eax,eax
    316d:	ff d1                	call   rcx
    316f:	8b 44 24 10          	mov    eax,DWORD PTR [rsp+0x10]
    3173:	48 8b 54 24 08       	mov    rdx,QWORD PTR [rsp+0x8]
    3178:	e9 6a ff ff ff       	jmp    30e7 <mlx_loop+0xa7>
    317d:	48 8b 84 24 d8 00 00 	mov    rax,QWORD PTR [rsp+0xd8]
    3184:	00 
    3185:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    318c:	00 00 
    318e:	75 0e                	jne    319e <mlx_loop+0x15e>
    3190:	48 81 c4 e0 00 00 00 	add    rsp,0xe0
    3197:	31 c0                	xor    eax,eax
    3199:	5b                   	pop    rbx
    319a:	5d                   	pop    rbp
    319b:	41 5c                	pop    r12
    319d:	c3                   	ret
    319e:	e8 cd f0 ff ff       	call   2270 <__stack_chk_fail@plt>
    31a3:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    31aa:	00 00 00 
    31ad:	0f 1f 00             	nop    DWORD PTR [rax]

00000000000031b0 <mlx_int_anti_resize_win>:
    31b0:	41 54                	push   r12
    31b2:	66 0f 6e ca          	movd   xmm1,edx
    31b6:	66 0f 6e c1          	movd   xmm0,ecx
    31ba:	55                   	push   rbp
    31bb:	66 0f 6f d1          	movdqa xmm2,xmm1
    31bf:	48 89 fd             	mov    rbp,rdi
    31c2:	53                   	push   rbx
    31c3:	66 0f 62 d0          	punpckldq xmm2,xmm0
    31c7:	48 89 f3             	mov    rbx,rsi
    31ca:	66 0f 6c d2          	punpcklqdq xmm2,xmm2
    31ce:	48 81 ec 90 00 00 00 	sub    rsp,0x90
    31d5:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    31d8:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    31df:	00 00 
    31e1:	48 89 84 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rax
    31e8:	00 
    31e9:	31 c0                	xor    eax,eax
    31eb:	4c 8d 64 24 30       	lea    r12,[rsp+0x30]
    31f0:	89 54 24 1c          	mov    DWORD PTR [rsp+0x1c],edx
    31f4:	89 4c 24 18          	mov    DWORD PTR [rsp+0x18],ecx
    31f8:	4c 89 e2             	mov    rdx,r12
    31fb:	48 8d 4c 24 28       	lea    rcx,[rsp+0x28]
    3200:	0f 29 14 24          	movaps XMMWORD PTR [rsp],xmm2
    3204:	e8 67 ee ff ff       	call   2070 <XGetWMNormalHints@plt>
    3209:	66 0f 6f 14 24       	movdqa xmm2,XMMWORD PTR [rsp]
    320e:	4c 89 e2             	mov    rdx,r12
    3211:	48 89 de             	mov    rsi,rbx
    3214:	66 0f 6e 4c 24 1c    	movd   xmm1,DWORD PTR [rsp+0x1c]
    321a:	66 0f 6e 44 24 18    	movd   xmm0,DWORD PTR [rsp+0x18]
    3220:	48 c7 44 24 30 3c 00 	mov    QWORD PTR [rsp+0x30],0x3c
    3227:	00 00 
    3229:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    322d:	0f 29 54 24 40       	movaps XMMWORD PTR [rsp+0x40],xmm2
    3232:	66 0f 7e 4c 24 50    	movd   DWORD PTR [rsp+0x50],xmm1
    3238:	66 0f 7e 44 24 54    	movd   DWORD PTR [rsp+0x54],xmm0
    323e:	e8 ad ee ff ff       	call   20f0 <XSetWMNormalHints@plt>
    3243:	48 8b 84 24 88 00 00 	mov    rax,QWORD PTR [rsp+0x88]
    324a:	00 
    324b:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3252:	00 00 
    3254:	75 0e                	jne    3264 <mlx_int_anti_resize_win+0xb4>
    3256:	48 81 c4 90 00 00 00 	add    rsp,0x90
    325d:	31 c0                	xor    eax,eax
    325f:	5b                   	pop    rbx
    3260:	5d                   	pop    rbp
    3261:	41 5c                	pop    r12
    3263:	c3                   	ret
    3264:	e8 07 f0 ff ff       	call   2270 <__stack_chk_fail@plt>
    3269:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000003270 <mlx_int_wait_first_expose>:
    3270:	55                   	push   rbp
    3271:	ba 00 80 00 00       	mov    edx,0x8000
    3276:	53                   	push   rbx
    3277:	48 89 fb             	mov    rbx,rdi
    327a:	48 81 ec d8 00 00 00 	sub    rsp,0xd8
    3281:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3284:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    328b:	00 00 
    328d:	48 89 84 24 c8 00 00 	mov    QWORD PTR [rsp+0xc8],rax
    3294:	00 
    3295:	31 c0                	xor    eax,eax
    3297:	48 89 e5             	mov    rbp,rsp
    329a:	48 89 e9             	mov    rcx,rbp
    329d:	e8 3e ef ff ff       	call   21e0 <XWindowEvent@plt>
    32a2:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    32a5:	48 89 ee             	mov    rsi,rbp
    32a8:	e8 63 ef ff ff       	call   2210 <XPutBackEvent@plt>
    32ad:	48 8b 84 24 c8 00 00 	mov    rax,QWORD PTR [rsp+0xc8]
    32b4:	00 
    32b5:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    32bc:	00 00 
    32be:	75 0c                	jne    32cc <mlx_int_wait_first_expose+0x5c>
    32c0:	48 81 c4 d8 00 00 00 	add    rsp,0xd8
    32c7:	31 c0                	xor    eax,eax
    32c9:	5b                   	pop    rbx
    32ca:	5d                   	pop    rbp
    32cb:	c3                   	ret
    32cc:	e8 9f ef ff ff       	call   2270 <__stack_chk_fail@plt>
    32d1:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    32d8:	00 00 00 
    32db:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

00000000000032e0 <mlx_int_get_visual>:
    32e0:	53                   	push   rbx
    32e1:	48 89 fb             	mov    rbx,rdi
    32e4:	48 83 ec 60          	sub    rsp,0x60
    32e8:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    32ef:	00 00 
    32f1:	48 89 44 24 58       	mov    QWORD PTR [rsp+0x58],rax
    32f6:	31 c0                	xor    eax,eax
    32f8:	c7 47 28 00 00 00 00 	mov    DWORD PTR [rdi+0x28],0x0
    32ff:	48 63 43 10          	movsxd rax,DWORD PTR [rbx+0x10]
    3303:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3306:	48 c1 e0 07          	shl    rax,0x7
    330a:	48 03 87 e8 00 00 00 	add    rax,QWORD PTR [rdi+0xe8]
    3311:	48 8b 40 40          	mov    rax,QWORD PTR [rax+0x40]
    3315:	83 78 10 04          	cmp    DWORD PTR [rax+0x10],0x4
    3319:	48 89 43 18          	mov    QWORD PTR [rbx+0x18],rax
    331d:	74 36                	je     3355 <mlx_int_get_visual+0x75>
    331f:	8b 43 14             	mov    eax,DWORD PTR [rbx+0x14]
    3322:	48 8d 4c 24 0c       	lea    rcx,[rsp+0xc]
    3327:	48 8d 54 24 10       	lea    rdx,[rsp+0x10]
    332c:	be 0c 00 00 00       	mov    esi,0xc
    3331:	c7 44 24 28 04 00 00 	mov    DWORD PTR [rsp+0x28],0x4
    3338:	00 
    3339:	89 44 24 24          	mov    DWORD PTR [rsp+0x24],eax
    333d:	e8 8e ef ff ff       	call   22d0 <XGetVisualInfo@plt>
    3342:	48 85 c0             	test   rax,rax
    3345:	74 26                	je     336d <mlx_int_get_visual+0x8d>
    3347:	48 8b 00             	mov    rax,QWORD PTR [rax]
    334a:	c7 43 28 01 00 00 00 	mov    DWORD PTR [rbx+0x28],0x1
    3351:	48 89 43 18          	mov    QWORD PTR [rbx+0x18],rax
    3355:	31 c0                	xor    eax,eax
    3357:	48 8b 54 24 58       	mov    rdx,QWORD PTR [rsp+0x58]
    335c:	64 48 2b 14 25 28 00 	sub    rdx,QWORD PTR fs:0x28
    3363:	00 00 
    3365:	75 0d                	jne    3374 <mlx_int_get_visual+0x94>
    3367:	48 83 c4 60          	add    rsp,0x60
    336b:	5b                   	pop    rbx
    336c:	c3                   	ret
    336d:	b8 ff ff ff ff       	mov    eax,0xffffffff
    3372:	eb e3                	jmp    3357 <mlx_int_get_visual+0x77>
    3374:	e8 f7 ee ff ff       	call   2270 <__stack_chk_fail@plt>
    3379:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000003380 <shm_att_pb>:
    3380:	8b 46 20             	mov    eax,DWORD PTR [rsi+0x20]
    3383:	25 00 ff ff 00       	and    eax,0xffff00
    3388:	3d 00 92 01 00       	cmp    eax,0x19200
    338d:	74 11                	je     33a0 <shm_att_pb+0x20>
    338f:	c7 05 6b 2f 00 00 01 	mov    DWORD PTR [rip+0x2f6b],0x1        # 6304 <mlx_X_error>
    3396:	00 00 00 
    3399:	c3                   	ret
    339a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    33a0:	48 83 ec 08          	sub    rsp,0x8
    33a4:	ba 38 00 00 00       	mov    edx,0x38
    33a9:	bf 02 00 00 00       	mov    edi,0x2
    33ae:	48 8d 35 fb 0d 00 00 	lea    rsi,[rip+0xdfb]        # 41b0 <_IO_stdin_used+0x1b0>
    33b5:	e8 86 ef ff ff       	call   2340 <write@plt>
    33ba:	c7 05 40 2f 00 00 01 	mov    DWORD PTR [rip+0x2f40],0x1        # 6304 <mlx_X_error>
    33c1:	00 00 00 
    33c4:	48 83 c4 08          	add    rsp,0x8
    33c8:	c3                   	ret
    33c9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000033d0 <mlx_int_new_xshm_image>:
    33d0:	41 57                	push   r15
    33d2:	41 56                	push   r14
    33d4:	41 55                	push   r13
    33d6:	41 89 cd             	mov    r13d,ecx
    33d9:	41 54                	push   r12
    33db:	41 89 d4             	mov    r12d,edx
    33de:	55                   	push   rbp
    33df:	89 f5                	mov    ebp,esi
    33e1:	be 01 00 00 00       	mov    esi,0x1
    33e6:	53                   	push   rbx
    33e7:	48 89 fb             	mov    rbx,rdi
    33ea:	bf 58 00 00 00       	mov    edi,0x58
    33ef:	48 83 ec 18          	sub    rsp,0x18
    33f3:	e8 a8 ee ff ff       	call   22a0 <calloc@plt>
    33f8:	48 85 c0             	test   rax,rax
    33fb:	0f 84 7e 01 00 00    	je     357f <mlx_int_new_xshm_image+0x1af>
    3401:	49 89 c6             	mov    r14,rax
    3404:	48 8d 40 38          	lea    rax,[rax+0x38]
    3408:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    340b:	8b 53 14             	mov    edx,DWORD PTR [rbx+0x14]
    340e:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
    3413:	48 8b 73 18          	mov    rsi,QWORD PTR [rbx+0x18]
    3417:	45 31 c0             	xor    r8d,r8d
    341a:	49 89 c1             	mov    r9,rax
    341d:	41 54                	push   r12
    341f:	44 89 e9             	mov    ecx,r13d
    3422:	55                   	push   rbp
    3423:	e8 78 ed ff ff       	call   21a0 <XShmCreateImage@plt>
    3428:	49 89 06             	mov    QWORD PTR [r14],rax
    342b:	5f                   	pop    rdi
    342c:	41 58                	pop    r8
    342e:	48 85 c0             	test   rax,rax
    3431:	0f 84 99 01 00 00    	je     35d0 <mlx_int_new_xshm_image+0x200>
    3437:	8d 75 20             	lea    esi,[rbp+0x20]
    343a:	66 0f 6e 40 2c       	movd   xmm0,DWORD PTR [rax+0x2c]
    343f:	66 0f 6e 50 30       	movd   xmm2,DWORD PTR [rax+0x30]
    3444:	31 ff                	xor    edi,edi
    3446:	41 0f af f4          	imul   esi,r12d
    344a:	66 41 0f 6e dc       	movd   xmm3,r12d
    344f:	66 0f 6e cd          	movd   xmm1,ebp
    3453:	45 89 6e 2c          	mov    DWORD PTR [r14+0x2c],r13d
    3457:	66 0f 62 c2          	punpckldq xmm0,xmm2
    345b:	66 0f 62 cb          	punpckldq xmm1,xmm3
    345f:	ba ff 03 00 00       	mov    edx,0x3ff
    3464:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
    3468:	c1 e6 02             	shl    esi,0x2
    346b:	41 0f 11 46 18       	movups XMMWORD PTR [r14+0x18],xmm0
    3470:	48 63 f6             	movsxd rsi,esi
    3473:	e8 38 ee ff ff       	call   22b0 <shmget@plt>
    3478:	41 89 46 40          	mov    DWORD PTR [r14+0x40],eax
    347c:	89 c7                	mov    edi,eax
    347e:	83 f8 ff             	cmp    eax,0xffffffff
    3481:	0f 84 e7 00 00 00    	je     356e <mlx_int_new_xshm_image+0x19e>
    3487:	4d 8b 3e             	mov    r15,QWORD PTR [r14]
    348a:	31 d2                	xor    edx,edx
    348c:	31 f6                	xor    esi,esi
    348e:	e8 ed ee ff ff       	call   2380 <shmat@plt>
    3493:	49 89 47 10          	mov    QWORD PTR [r15+0x10],rax
    3497:	49 89 46 48          	mov    QWORD PTR [r14+0x48],rax
    349b:	49 89 46 30          	mov    QWORD PTR [r14+0x30],rax
    349f:	48 83 f8 ff          	cmp    rax,0xffffffffffffffff
    34a3:	0f 84 b8 00 00 00    	je     3561 <mlx_int_new_xshm_image+0x191>
    34a9:	41 c7 46 50 00 00 00 	mov    DWORD PTR [r14+0x50],0x0
    34b0:	00 
    34b1:	48 8d 3d c8 fe ff ff 	lea    rdi,[rip+0xfffffffffffffec8]        # 3380 <shm_att_pb>
    34b8:	c7 05 42 2e 00 00 00 	mov    DWORD PTR [rip+0x2e42],0x0        # 6304 <mlx_X_error>
    34bf:	00 00 00 
    34c2:	e8 29 ee ff ff       	call   22f0 <XSetErrorHandler@plt>
    34c7:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    34ca:	48 8b 74 24 08       	mov    rsi,QWORD PTR [rsp+0x8]
    34cf:	49 89 c7             	mov    r15,rax
    34d2:	e8 b9 ed ff ff       	call   2290 <XShmAttach@plt>
    34d7:	85 c0                	test   eax,eax
    34d9:	74 75                	je     3550 <mlx_int_new_xshm_image+0x180>
    34db:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    34de:	31 f6                	xor    esi,esi
    34e0:	e8 7b ed ff ff       	call   2260 <XSync@plt>
    34e5:	8b 35 19 2e 00 00    	mov    esi,DWORD PTR [rip+0x2e19]        # 6304 <mlx_X_error>
    34eb:	85 f6                	test   esi,esi
    34ed:	75 61                	jne    3550 <mlx_int_new_xshm_image+0x180>
    34ef:	4c 89 ff             	mov    rdi,r15
    34f2:	e8 f9 ed ff ff       	call   22f0 <XSetErrorHandler@plt>
    34f7:	41 8b 7e 40          	mov    edi,DWORD PTR [r14+0x40]
    34fb:	31 d2                	xor    edx,edx
    34fd:	31 f6                	xor    esi,esi
    34ff:	e8 fc ed ff ff       	call   2300 <shmctl@plt>
    3504:	44 39 6b 4c          	cmp    DWORD PTR [rbx+0x4c],r13d
    3508:	0f 84 8a 00 00 00    	je     3598 <mlx_int_new_xshm_image+0x1c8>
    350e:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    3512:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    3515:	89 ea                	mov    edx,ebp
    3517:	44 89 e1             	mov    ecx,r12d
    351a:	44 8b 43 14          	mov    r8d,DWORD PTR [rbx+0x14]
    351e:	e8 ed ed ff ff       	call   2310 <XCreatePixmap@plt>
    3523:	ba 02 00 00 00       	mov    edx,0x2
    3528:	49 89 46 08          	mov    QWORD PTR [r14+0x8],rax
    352c:	8b 43 50             	mov    eax,DWORD PTR [rbx+0x50]
    352f:	41 89 56 28          	mov    DWORD PTR [r14+0x28],edx
    3533:	85 c0                	test   eax,eax
    3535:	75 51                	jne    3588 <mlx_int_new_xshm_image+0x1b8>
    3537:	48 83 c4 18          	add    rsp,0x18
    353b:	4c 89 f0             	mov    rax,r14
    353e:	5b                   	pop    rbx
    353f:	5d                   	pop    rbp
    3540:	41 5c                	pop    r12
    3542:	41 5d                	pop    r13
    3544:	41 5e                	pop    r14
    3546:	41 5f                	pop    r15
    3548:	c3                   	ret
    3549:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    3550:	4c 89 ff             	mov    rdi,r15
    3553:	e8 98 ed ff ff       	call   22f0 <XSetErrorHandler@plt>
    3558:	49 8b 7e 30          	mov    rdi,QWORD PTR [r14+0x30]
    355c:	e8 df ea ff ff       	call   2040 <shmdt@plt>
    3561:	41 8b 7e 40          	mov    edi,DWORD PTR [r14+0x40]
    3565:	31 d2                	xor    edx,edx
    3567:	31 f6                	xor    esi,esi
    3569:	e8 92 ed ff ff       	call   2300 <shmctl@plt>
    356e:	49 8b 06             	mov    rax,QWORD PTR [r14]
    3571:	48 89 c7             	mov    rdi,rax
    3574:	ff 50 60             	call   QWORD PTR [rax+0x60]
    3577:	4c 89 f7             	mov    rdi,r14
    357a:	e8 d1 eb ff ff       	call   2150 <free@plt>
    357f:	45 31 f6             	xor    r14d,r14d
    3582:	eb b3                	jmp    3537 <mlx_int_new_xshm_image+0x167>
    3584:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    3588:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    358b:	e8 b0 ec ff ff       	call   2240 <XFlush@plt>
    3590:	eb a5                	jmp    3537 <mlx_int_new_xshm_image+0x167>
    3592:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3598:	8b 43 14             	mov    eax,DWORD PTR [rbx+0x14]
    359b:	48 83 ec 08          	sub    rsp,0x8
    359f:	49 8b 56 48          	mov    rdx,QWORD PTR [r14+0x48]
    35a3:	45 89 e1             	mov    r9d,r12d
    35a6:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    35aa:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    35ad:	41 89 e8             	mov    r8d,ebp
    35b0:	50                   	push   rax
    35b1:	48 8b 4c 24 18       	mov    rcx,QWORD PTR [rsp+0x18]
    35b6:	e8 05 eb ff ff       	call   20c0 <XShmCreatePixmap@plt>
    35bb:	5a                   	pop    rdx
    35bc:	ba 03 00 00 00       	mov    edx,0x3
    35c1:	59                   	pop    rcx
    35c2:	e9 61 ff ff ff       	jmp    3528 <mlx_int_new_xshm_image+0x158>
    35c7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    35ce:	00 00 
    35d0:	4c 89 f7             	mov    rdi,r14
    35d3:	e8 78 eb ff ff       	call   2150 <free@plt>
    35d8:	eb a5                	jmp    357f <mlx_int_new_xshm_image+0x1af>
    35da:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000000035e0 <mlx_int_new_image>:
    35e0:	41 56                	push   r14
    35e2:	41 89 ce             	mov    r14d,ecx
    35e5:	41 55                	push   r13
    35e7:	41 89 d5             	mov    r13d,edx
    35ea:	41 54                	push   r12
    35ec:	41 89 f4             	mov    r12d,esi
    35ef:	55                   	push   rbp
    35f0:	48 89 fd             	mov    rbp,rdi
    35f3:	bf 58 00 00 00       	mov    edi,0x58
    35f8:	53                   	push   rbx
    35f9:	e8 e2 ea ff ff       	call   20e0 <malloc@plt>
    35fe:	48 85 c0             	test   rax,rax
    3601:	0f 84 f2 00 00 00    	je     36f9 <mlx_int_new_image+0x119>
    3607:	41 8d 7c 24 20       	lea    edi,[r12+0x20]
    360c:	be 01 00 00 00       	mov    esi,0x1
    3611:	48 89 c3             	mov    rbx,rax
    3614:	41 0f af fd          	imul   edi,r13d
    3618:	c1 e7 02             	shl    edi,0x2
    361b:	48 63 ff             	movsxd rdi,edi
    361e:	e8 7d ec ff ff       	call   22a0 <calloc@plt>
    3623:	48 89 43 30          	mov    QWORD PTR [rbx+0x30],rax
    3627:	49 89 c1             	mov    r9,rax
    362a:	48 85 c0             	test   rax,rax
    362d:	0f 84 ca 00 00 00    	je     36fd <mlx_int_new_image+0x11d>
    3633:	8b 55 14             	mov    edx,DWORD PTR [rbp+0x14]
    3636:	48 8b 75 18          	mov    rsi,QWORD PTR [rbp+0x18]
    363a:	45 31 c0             	xor    r8d,r8d
    363d:	44 89 f1             	mov    ecx,r14d
    3640:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3644:	6a 00                	push   0x0
    3646:	6a 20                	push   0x20
    3648:	41 55                	push   r13
    364a:	41 54                	push   r12
    364c:	e8 5f ea ff ff       	call   20b0 <XCreateImage@plt>
    3651:	48 83 c4 20          	add    rsp,0x20
    3655:	48 89 03             	mov    QWORD PTR [rbx],rax
    3658:	48 85 c0             	test   rax,rax
    365b:	0f 84 87 00 00 00    	je     36e8 <mlx_int_new_image+0x108>
    3661:	66 0f 6e 40 2c       	movd   xmm0,DWORD PTR [rax+0x2c]
    3666:	66 0f 6e 58 30       	movd   xmm3,DWORD PTR [rax+0x30]
    366b:	44 89 e9             	mov    ecx,r13d
    366e:	44 89 e2             	mov    edx,r12d
    3671:	66 41 0f 6e d5       	movd   xmm2,r13d
    3676:	66 41 0f 6e cc       	movd   xmm1,r12d
    367b:	48 8b 75 08          	mov    rsi,QWORD PTR [rbp+0x8]
    367f:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3683:	66 0f 62 ca          	punpckldq xmm1,xmm2
    3687:	66 0f 62 c3          	punpckldq xmm0,xmm3
    368b:	48 c7 43 10 00 00 00 	mov    QWORD PTR [rbx+0x10],0x0
    3692:	00 
    3693:	44 8b 45 14          	mov    r8d,DWORD PTR [rbp+0x14]
    3697:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
    369b:	0f 11 43 18          	movups XMMWORD PTR [rbx+0x18],xmm0
    369f:	e8 6c ec ff ff       	call   2310 <XCreatePixmap@plt>
    36a4:	44 89 73 2c          	mov    DWORD PTR [rbx+0x2c],r14d
    36a8:	48 89 43 08          	mov    QWORD PTR [rbx+0x8],rax
    36ac:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    36af:	c7 43 28 01 00 00 00 	mov    DWORD PTR [rbx+0x28],0x1
    36b6:	85 c0                	test   eax,eax
    36b8:	75 16                	jne    36d0 <mlx_int_new_image+0xf0>
    36ba:	48 89 d8             	mov    rax,rbx
    36bd:	5b                   	pop    rbx
    36be:	5d                   	pop    rbp
    36bf:	41 5c                	pop    r12
    36c1:	41 5d                	pop    r13
    36c3:	41 5e                	pop    r14
    36c5:	c3                   	ret
    36c6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    36cd:	00 00 00 
    36d0:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    36d4:	e8 67 eb ff ff       	call   2240 <XFlush@plt>
    36d9:	48 89 d8             	mov    rax,rbx
    36dc:	5b                   	pop    rbx
    36dd:	5d                   	pop    rbp
    36de:	41 5c                	pop    r12
    36e0:	41 5d                	pop    r13
    36e2:	41 5e                	pop    r14
    36e4:	c3                   	ret
    36e5:	0f 1f 00             	nop    DWORD PTR [rax]
    36e8:	48 8b 7b 30          	mov    rdi,QWORD PTR [rbx+0x30]
    36ec:	e8 5f ea ff ff       	call   2150 <free@plt>
    36f1:	48 89 df             	mov    rdi,rbx
    36f4:	e8 57 ea ff ff       	call   2150 <free@plt>
    36f9:	31 db                	xor    ebx,ebx
    36fb:	eb bd                	jmp    36ba <mlx_int_new_image+0xda>
    36fd:	48 89 df             	mov    rdi,rbx
    3700:	31 db                	xor    ebx,ebx
    3702:	e8 49 ea ff ff       	call   2150 <free@plt>
    3707:	eb b1                	jmp    36ba <mlx_int_new_image+0xda>
    3709:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000003710 <mlx_new_image>:
    3710:	41 54                	push   r12
    3712:	41 89 d4             	mov    r12d,edx
    3715:	55                   	push   rbp
    3716:	89 f5                	mov    ebp,esi
    3718:	53                   	push   rbx
    3719:	8b 47 48             	mov    eax,DWORD PTR [rdi+0x48]
    371c:	48 89 fb             	mov    rbx,rdi
    371f:	85 c0                	test   eax,eax
    3721:	74 1d                	je     3740 <mlx_new_image+0x30>
    3723:	b9 02 00 00 00       	mov    ecx,0x2
    3728:	e8 a3 fc ff ff       	call   33d0 <mlx_int_new_xshm_image>
    372d:	48 85 c0             	test   rax,rax
    3730:	74 0e                	je     3740 <mlx_new_image+0x30>
    3732:	5b                   	pop    rbx
    3733:	5d                   	pop    rbp
    3734:	41 5c                	pop    r12
    3736:	c3                   	ret
    3737:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    373e:	00 00 
    3740:	44 89 e2             	mov    edx,r12d
    3743:	89 ee                	mov    esi,ebp
    3745:	48 89 df             	mov    rdi,rbx
    3748:	b9 02 00 00 00       	mov    ecx,0x2
    374d:	5b                   	pop    rbx
    374e:	5d                   	pop    rbp
    374f:	41 5c                	pop    r12
    3751:	e9 8a fe ff ff       	jmp    35e0 <mlx_int_new_image>
    3756:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    375d:	00 00 00 

0000000000003760 <mlx_new_image2>:
    3760:	41 54                	push   r12
    3762:	41 89 d4             	mov    r12d,edx
    3765:	55                   	push   rbp
    3766:	89 f5                	mov    ebp,esi
    3768:	53                   	push   rbx
    3769:	8b 47 48             	mov    eax,DWORD PTR [rdi+0x48]
    376c:	48 89 fb             	mov    rbx,rdi
    376f:	85 c0                	test   eax,eax
    3771:	74 1d                	je     3790 <mlx_new_image2+0x30>
    3773:	b9 01 00 00 00       	mov    ecx,0x1
    3778:	e8 53 fc ff ff       	call   33d0 <mlx_int_new_xshm_image>
    377d:	48 85 c0             	test   rax,rax
    3780:	74 0e                	je     3790 <mlx_new_image2+0x30>
    3782:	5b                   	pop    rbx
    3783:	5d                   	pop    rbp
    3784:	41 5c                	pop    r12
    3786:	c3                   	ret
    3787:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    378e:	00 00 
    3790:	44 89 e2             	mov    edx,r12d
    3793:	89 ee                	mov    esi,ebp
    3795:	48 89 df             	mov    rdi,rbx
    3798:	b9 01 00 00 00       	mov    ecx,0x1
    379d:	5b                   	pop    rbx
    379e:	5d                   	pop    rbp
    379f:	41 5c                	pop    r12
    37a1:	e9 3a fe ff ff       	jmp    35e0 <mlx_int_new_image>
    37a6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    37ad:	00 00 00 

00000000000037b0 <mlx_put_image_to_window>:
    37b0:	41 57                	push   r15
    37b2:	41 56                	push   r14
    37b4:	45 89 c6             	mov    r14d,r8d
    37b7:	41 55                	push   r13
    37b9:	41 89 cd             	mov    r13d,ecx
    37bc:	41 54                	push   r12
    37be:	49 89 f4             	mov    r12,rsi
    37c1:	55                   	push   rbp
    37c2:	48 89 fd             	mov    rbp,rdi
    37c5:	53                   	push   rbx
    37c6:	48 89 d3             	mov    rbx,rdx
    37c9:	48 83 ec 18          	sub    rsp,0x18
    37cd:	4c 8b 7a 10          	mov    r15,QWORD PTR [rdx+0x10]
    37d1:	4c 8b 56 08          	mov    r10,QWORD PTR [rsi+0x8]
    37d5:	4d 85 ff             	test   r15,r15
    37d8:	74 14                	je     37ee <mlx_put_image_to_window+0x3e>
    37da:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    37dd:	44 89 c1             	mov    ecx,r8d
    37e0:	44 89 ea             	mov    edx,r13d
    37e3:	4c 89 fe             	mov    rsi,r15
    37e6:	e8 65 eb ff ff       	call   2350 <XSetClipOrigin@plt>
    37eb:	4d 89 fa             	mov    r10,r15
    37ee:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    37f1:	83 f8 02             	cmp    eax,0x2
    37f4:	0f 84 a6 00 00 00    	je     38a0 <mlx_put_image_to_window+0xf0>
    37fa:	83 f8 01             	cmp    eax,0x1
    37fd:	74 61                	je     3860 <mlx_put_image_to_window+0xb0>
    37ff:	49 8b 14 24          	mov    rdx,QWORD PTR [r12]
    3803:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    3807:	45 31 c9             	xor    r9d,r9d
    380a:	45 31 c0             	xor    r8d,r8d
    380d:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3811:	41 56                	push   r14
    3813:	4c 89 d1             	mov    rcx,r10
    3816:	41 55                	push   r13
    3818:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    381b:	50                   	push   rax
    381c:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    381f:	50                   	push   rax
    3820:	e8 3b e9 ff ff       	call   2160 <XCopyArea@plt>
    3825:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    3828:	48 83 c4 20          	add    rsp,0x20
    382c:	85 c0                	test   eax,eax
    382e:	75 10                	jne    3840 <mlx_put_image_to_window+0x90>
    3830:	48 83 c4 18          	add    rsp,0x18
    3834:	5b                   	pop    rbx
    3835:	5d                   	pop    rbp
    3836:	41 5c                	pop    r12
    3838:	41 5d                	pop    r13
    383a:	41 5e                	pop    r14
    383c:	41 5f                	pop    r15
    383e:	c3                   	ret
    383f:	90                   	nop
    3840:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3844:	48 83 c4 18          	add    rsp,0x18
    3848:	5b                   	pop    rbx
    3849:	5d                   	pop    rbp
    384a:	41 5c                	pop    r12
    384c:	41 5d                	pop    r13
    384e:	41 5e                	pop    r14
    3850:	41 5f                	pop    r15
    3852:	e9 e9 e9 ff ff       	jmp    2240 <XFlush@plt>
    3857:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    385e:	00 00 
    3860:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    3863:	4c 89 54 24 08       	mov    QWORD PTR [rsp+0x8],r10
    3868:	45 31 c9             	xor    r9d,r9d
    386b:	45 31 c0             	xor    r8d,r8d
    386e:	48 8b 0b             	mov    rcx,QWORD PTR [rbx]
    3871:	49 8b 54 24 08       	mov    rdx,QWORD PTR [r12+0x8]
    3876:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    387a:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    387e:	50                   	push   rax
    387f:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    3882:	50                   	push   rax
    3883:	6a 00                	push   0x0
    3885:	6a 00                	push   0x0
    3887:	e8 f4 e9 ff ff       	call   2280 <XPutImage@plt>
    388c:	48 83 c4 20          	add    rsp,0x20
    3890:	4c 8b 54 24 08       	mov    r10,QWORD PTR [rsp+0x8]
    3895:	e9 65 ff ff ff       	jmp    37ff <mlx_put_image_to_window+0x4f>
    389a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    38a0:	4c 89 54 24 08       	mov    QWORD PTR [rsp+0x8],r10
    38a5:	48 83 ec 08          	sub    rsp,0x8
    38a9:	48 8b 0b             	mov    rcx,QWORD PTR [rbx]
    38ac:	45 31 c9             	xor    r9d,r9d
    38af:	49 8b 54 24 08       	mov    rdx,QWORD PTR [r12+0x8]
    38b4:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    38b8:	45 31 c0             	xor    r8d,r8d
    38bb:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    38bf:	6a 00                	push   0x0
    38c1:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    38c4:	50                   	push   rax
    38c5:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    38c8:	50                   	push   rax
    38c9:	6a 00                	push   0x0
    38cb:	6a 00                	push   0x0
    38cd:	e8 0e ea ff ff       	call   22e0 <XShmPutImage@plt>
    38d2:	48 83 c4 30          	add    rsp,0x30
    38d6:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    38d9:	4c 8b 54 24 08       	mov    r10,QWORD PTR [rsp+0x8]
    38de:	e9 17 ff ff ff       	jmp    37fa <mlx_put_image_to_window+0x4a>
    38e3:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    38ea:	00 00 00 
    38ed:	0f 1f 00             	nop    DWORD PTR [rax]

00000000000038f0 <mlx_destroy_window>:
    38f0:	55                   	push   rbp
    38f1:	48 89 fd             	mov    rbp,rdi
    38f4:	53                   	push   rbx
    38f5:	48 89 f3             	mov    rbx,rsi
    38f8:	48 81 ec b8 03 00 00 	sub    rsp,0x3b8
    38ff:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    3906:	00 00 
    3908:	48 89 84 24 a8 03 00 	mov    QWORD PTR [rsp+0x3a8],rax
    390f:	00 
    3910:	48 8b 47 30          	mov    rax,QWORD PTR [rdi+0x30]
    3914:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
    3919:	48 85 c0             	test   rax,rax
    391c:	74 30                	je     394e <mlx_destroy_window+0x5e>
    391e:	48 89 e1             	mov    rcx,rsp
    3921:	eb 14                	jmp    3937 <mlx_destroy_window+0x47>
    3923:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    3928:	48 8b 50 10          	mov    rdx,QWORD PTR [rax+0x10]
    392c:	48 85 d2             	test   rdx,rdx
    392f:	74 18                	je     3949 <mlx_destroy_window+0x59>
    3931:	48 89 c1             	mov    rcx,rax
    3934:	48 89 d0             	mov    rax,rdx
    3937:	48 39 c3             	cmp    rbx,rax
    393a:	75 ec                	jne    3928 <mlx_destroy_window+0x38>
    393c:	48 8b 53 10          	mov    rdx,QWORD PTR [rbx+0x10]
    3940:	48 89 51 10          	mov    QWORD PTR [rcx+0x10],rdx
    3944:	48 85 d2             	test   rdx,rdx
    3947:	75 eb                	jne    3934 <mlx_destroy_window+0x44>
    3949:	48 8b 44 24 10       	mov    rax,QWORD PTR [rsp+0x10]
    394e:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
    3951:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3955:	48 89 45 30          	mov    QWORD PTR [rbp+0x30],rax
    3959:	e8 22 e8 ff ff       	call   2180 <XDestroyWindow@plt>
    395e:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    3962:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3966:	e8 45 e8 ff ff       	call   21b0 <XFreeGC@plt>
    396b:	48 89 df             	mov    rdi,rbx
    396e:	e8 dd e7 ff ff       	call   2150 <free@plt>
    3973:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    3976:	85 c0                	test   eax,eax
    3978:	75 26                	jne    39a0 <mlx_destroy_window+0xb0>
    397a:	48 8b 84 24 a8 03 00 	mov    rax,QWORD PTR [rsp+0x3a8]
    3981:	00 
    3982:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3989:	00 00 
    398b:	75 38                	jne    39c5 <mlx_destroy_window+0xd5>
    398d:	48 81 c4 b8 03 00 00 	add    rsp,0x3b8
    3994:	31 c0                	xor    eax,eax
    3996:	5b                   	pop    rbx
    3997:	5d                   	pop    rbp
    3998:	c3                   	ret
    3999:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    39a0:	48 8b 84 24 a8 03 00 	mov    rax,QWORD PTR [rsp+0x3a8]
    39a7:	00 
    39a8:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    39af:	00 00 
    39b1:	75 12                	jne    39c5 <mlx_destroy_window+0xd5>
    39b3:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    39b7:	48 81 c4 b8 03 00 00 	add    rsp,0x3b8
    39be:	5b                   	pop    rbx
    39bf:	5d                   	pop    rbp
    39c0:	e9 7b e8 ff ff       	jmp    2240 <XFlush@plt>
    39c5:	e8 a6 e8 ff ff       	call   2270 <__stack_chk_fail@plt>
    39ca:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000000039d0 <mlx_int_param_undef>:
    39d0:	c3                   	ret
    39d1:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    39d8:	00 00 00 00 
    39dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000000039e0 <mlx_int_param_ButtonPress>:
    39e0:	44 8b 4e 44          	mov    r9d,DWORD PTR [rsi+0x44]
    39e4:	8b 46 40             	mov    eax,DWORD PTR [rsi+0x40]
    39e7:	48 8b 8a b8 00 00 00 	mov    rcx,QWORD PTR [rdx+0xb8]
    39ee:	8b 7e 54             	mov    edi,DWORD PTR [rsi+0x54]
    39f1:	4c 8b 82 b0 00 00 00 	mov    r8,QWORD PTR [rdx+0xb0]
    39f8:	89 c6                	mov    esi,eax
    39fa:	44 89 ca             	mov    edx,r9d
    39fd:	31 c0                	xor    eax,eax
    39ff:	41 ff e0             	jmp    r8
    3a02:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    3a09:	00 00 00 00 
    3a0d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000003a10 <mlx_int_param_ButtonRelease>:
    3a10:	44 8b 4e 44          	mov    r9d,DWORD PTR [rsi+0x44]
    3a14:	8b 46 40             	mov    eax,DWORD PTR [rsi+0x40]
    3a17:	48 8b 8a d0 00 00 00 	mov    rcx,QWORD PTR [rdx+0xd0]
    3a1e:	8b 7e 54             	mov    edi,DWORD PTR [rsi+0x54]
    3a21:	4c 8b 82 c8 00 00 00 	mov    r8,QWORD PTR [rdx+0xc8]
    3a28:	89 c6                	mov    esi,eax
    3a2a:	44 89 ca             	mov    edx,r9d
    3a2d:	31 c0                	xor    eax,eax
    3a2f:	41 ff e0             	jmp    r8
    3a32:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    3a39:	00 00 00 00 
    3a3d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000003a40 <mlx_int_param_MotionNotify>:
    3a40:	8b 46 44             	mov    eax,DWORD PTR [rsi+0x44]
    3a43:	4c 8b 82 e8 00 00 00 	mov    r8,QWORD PTR [rdx+0xe8]
    3a4a:	8b 7e 40             	mov    edi,DWORD PTR [rsi+0x40]
    3a4d:	48 8b 8a e0 00 00 00 	mov    rcx,QWORD PTR [rdx+0xe0]
    3a54:	89 c6                	mov    esi,eax
    3a56:	4c 89 c2             	mov    rdx,r8
    3a59:	31 c0                	xor    eax,eax
    3a5b:	ff e1                	jmp    rcx
    3a5d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000003a60 <mlx_int_param_generic>:
    3a60:	48 63 06             	movsxd rax,DWORD PTR [rsi]
    3a63:	48 8d 04 40          	lea    rax,[rax+rax*2]
    3a67:	48 8d 04 c2          	lea    rax,[rdx+rax*8]
    3a6b:	48 8b 78 58          	mov    rdi,QWORD PTR [rax+0x58]
    3a6f:	48 8b 50 50          	mov    rdx,QWORD PTR [rax+0x50]
    3a73:	31 c0                	xor    eax,eax
    3a75:	ff e2                	jmp    rdx
    3a77:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    3a7e:	00 00 

0000000000003a80 <mlx_int_param_KeyPress>:
    3a80:	55                   	push   rbp
    3a81:	31 c9                	xor    ecx,ecx
    3a83:	53                   	push   rbx
    3a84:	48 83 ec 08          	sub    rsp,0x8
    3a88:	0f b6 76 54          	movzx  esi,BYTE PTR [rsi+0x54]
    3a8c:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3a8f:	48 8b 9a 80 00 00 00 	mov    rbx,QWORD PTR [rdx+0x80]
    3a96:	48 8b aa 88 00 00 00 	mov    rbp,QWORD PTR [rdx+0x88]
    3a9d:	31 d2                	xor    edx,edx
    3a9f:	e8 6c e6 ff ff       	call   2110 <XkbKeycodeToKeysym@plt>
    3aa4:	48 83 c4 08          	add    rsp,0x8
    3aa8:	48 89 c7             	mov    rdi,rax
    3aab:	48 89 ee             	mov    rsi,rbp
    3aae:	48 89 d9             	mov    rcx,rbx
    3ab1:	31 c0                	xor    eax,eax
    3ab3:	5b                   	pop    rbx
    3ab4:	5d                   	pop    rbp
    3ab5:	ff e1                	jmp    rcx
    3ab7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    3abe:	00 00 

0000000000003ac0 <mlx_int_param_KeyRelease>:
    3ac0:	55                   	push   rbp
    3ac1:	31 c9                	xor    ecx,ecx
    3ac3:	53                   	push   rbx
    3ac4:	48 83 ec 08          	sub    rsp,0x8
    3ac8:	0f b6 76 54          	movzx  esi,BYTE PTR [rsi+0x54]
    3acc:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3acf:	48 8b 9a 98 00 00 00 	mov    rbx,QWORD PTR [rdx+0x98]
    3ad6:	48 8b aa a0 00 00 00 	mov    rbp,QWORD PTR [rdx+0xa0]
    3add:	31 d2                	xor    edx,edx
    3adf:	e8 2c e6 ff ff       	call   2110 <XkbKeycodeToKeysym@plt>
    3ae4:	48 83 c4 08          	add    rsp,0x8
    3ae8:	48 89 c7             	mov    rdi,rax
    3aeb:	48 89 ee             	mov    rsi,rbp
    3aee:	48 89 d9             	mov    rcx,rbx
    3af1:	31 c0                	xor    eax,eax
    3af3:	5b                   	pop    rbx
    3af4:	5d                   	pop    rbp
    3af5:	ff e1                	jmp    rcx
    3af7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    3afe:	00 00 

0000000000003b00 <mlx_int_param_Expose>:
    3b00:	8b 46 38             	mov    eax,DWORD PTR [rsi+0x38]
    3b03:	85 c0                	test   eax,eax
    3b05:	75 19                	jne    3b20 <mlx_int_param_Expose+0x20>
    3b07:	48 8b ba 78 01 00 00 	mov    rdi,QWORD PTR [rdx+0x178]
    3b0e:	31 c0                	xor    eax,eax
    3b10:	48 8b 92 70 01 00 00 	mov    rdx,QWORD PTR [rdx+0x170]
    3b17:	ff e2                	jmp    rdx
    3b19:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    3b20:	c3                   	ret
    3b21:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    3b28:	00 00 00 
    3b2b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000003b30 <mlx_int_set_win_event_mask>:
    3b30:	41 55                	push   r13
    3b32:	49 89 fd             	mov    r13,rdi
    3b35:	41 54                	push   r12
    3b37:	55                   	push   rbp
    3b38:	48 bd 00 00 00 00 ff 	movabs rbp,0xffffffff00000000
    3b3f:	ff ff ff 
    3b42:	53                   	push   rbx
    3b43:	48 81 ec 18 01 00 00 	sub    rsp,0x118
    3b4a:	48 8b 5f 30          	mov    rbx,QWORD PTR [rdi+0x30]
    3b4e:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    3b55:	00 00 
    3b57:	48 89 84 24 08 01 00 	mov    QWORD PTR [rsp+0x108],rax
    3b5e:	00 
    3b5f:	31 c0                	xor    eax,eax
    3b61:	4c 8d a4 24 90 00 00 	lea    r12,[rsp+0x90]
    3b68:	00 
    3b69:	48 85 db             	test   rbx,rbx
    3b6c:	0f 84 ec 03 00 00    	je     3f5e <mlx_int_set_win_event_mask+0x42e>
    3b72:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3b78:	8b 83 78 03 00 00    	mov    eax,DWORD PTR [rbx+0x378]
    3b7e:	8b 93 90 03 00 00    	mov    edx,DWORD PTR [rbx+0x390]
    3b84:	66 0f ef ed          	pxor   xmm5,xmm5
    3b88:	4c 89 e1             	mov    rcx,r12
    3b8b:	0f 29 2c 24          	movaps XMMWORD PTR [rsp],xmm5
    3b8f:	66 0f 6f cd          	movdqa xmm1,xmm5
    3b93:	66 0f 6f d5          	movdqa xmm2,xmm5
    3b97:	48 c1 e0 20          	shl    rax,0x20
    3b9b:	0f 29 6c 24 10       	movaps XMMWORD PTR [rsp+0x10],xmm5
    3ba0:	48 09 c2             	or     rdx,rax
    3ba3:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
    3ba8:	0f 29 6c 24 20       	movaps XMMWORD PTR [rsp+0x20],xmm5
    3bad:	48 89 14 24          	mov    QWORD PTR [rsp],rdx
    3bb1:	8b 93 60 03 00 00    	mov    edx,DWORD PTR [rbx+0x360]
    3bb7:	48 21 e8             	and    rax,rbp
    3bba:	0f 29 6c 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm5
    3bbf:	48 09 d0             	or     rax,rdx
    3bc2:	8b 93 48 03 00 00    	mov    edx,DWORD PTR [rbx+0x348]
    3bc8:	89 c0                	mov    eax,eax
    3bca:	48 c1 e2 20          	shl    rdx,0x20
    3bce:	48 09 d0             	or     rax,rdx
    3bd1:	8b 93 30 03 00 00    	mov    edx,DWORD PTR [rbx+0x330]
    3bd7:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
    3bdc:	8b 83 18 03 00 00    	mov    eax,DWORD PTR [rbx+0x318]
    3be2:	48 c1 e0 20          	shl    rax,0x20
    3be6:	48 09 c2             	or     rdx,rax
    3be9:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
    3bee:	48 89 54 24 10       	mov    QWORD PTR [rsp+0x10],rdx
    3bf3:	8b 93 00 03 00 00    	mov    edx,DWORD PTR [rbx+0x300]
    3bf9:	48 21 e8             	and    rax,rbp
    3bfc:	48 09 d0             	or     rax,rdx
    3bff:	8b 93 e8 02 00 00    	mov    edx,DWORD PTR [rbx+0x2e8]
    3c05:	89 c0                	mov    eax,eax
    3c07:	48 c1 e2 20          	shl    rdx,0x20
    3c0b:	48 09 d0             	or     rax,rdx
    3c0e:	8b 93 d0 02 00 00    	mov    edx,DWORD PTR [rbx+0x2d0]
    3c14:	48 89 44 24 18       	mov    QWORD PTR [rsp+0x18],rax
    3c19:	8b 83 b8 02 00 00    	mov    eax,DWORD PTR [rbx+0x2b8]
    3c1f:	48 c1 e0 20          	shl    rax,0x20
    3c23:	48 09 c2             	or     rdx,rax
    3c26:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
    3c2b:	48 89 54 24 20       	mov    QWORD PTR [rsp+0x20],rdx
    3c30:	8b 93 a0 02 00 00    	mov    edx,DWORD PTR [rbx+0x2a0]
    3c36:	48 21 e8             	and    rax,rbp
    3c39:	48 09 d0             	or     rax,rdx
    3c3c:	8b 93 88 02 00 00    	mov    edx,DWORD PTR [rbx+0x288]
    3c42:	89 c0                	mov    eax,eax
    3c44:	48 c1 e2 20          	shl    rdx,0x20
    3c48:	48 09 d0             	or     rax,rdx
    3c4b:	8b 93 70 02 00 00    	mov    edx,DWORD PTR [rbx+0x270]
    3c51:	48 89 44 24 28       	mov    QWORD PTR [rsp+0x28],rax
    3c56:	8b 83 58 02 00 00    	mov    eax,DWORD PTR [rbx+0x258]
    3c5c:	48 c1 e0 20          	shl    rax,0x20
    3c60:	48 09 c2             	or     rdx,rax
    3c63:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
    3c68:	48 89 54 24 30       	mov    QWORD PTR [rsp+0x30],rdx
    3c6d:	8b 93 40 02 00 00    	mov    edx,DWORD PTR [rbx+0x240]
    3c73:	48 21 e8             	and    rax,rbp
    3c76:	48 09 d0             	or     rax,rdx
    3c79:	8b 93 28 02 00 00    	mov    edx,DWORD PTR [rbx+0x228]
    3c7f:	89 c0                	mov    eax,eax
    3c81:	48 c1 e2 20          	shl    rdx,0x20
    3c85:	48 09 d0             	or     rax,rdx
    3c88:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
    3c8d:	0f 29 6c 24 40       	movaps XMMWORD PTR [rsp+0x40],xmm5
    3c92:	8b 83 f8 01 00 00    	mov    eax,DWORD PTR [rbx+0x1f8]
    3c98:	8b 93 10 02 00 00    	mov    edx,DWORD PTR [rbx+0x210]
    3c9e:	0f 29 6c 24 50       	movaps XMMWORD PTR [rsp+0x50],xmm5
    3ca3:	48 c1 e0 20          	shl    rax,0x20
    3ca7:	0f 29 6c 24 60       	movaps XMMWORD PTR [rsp+0x60],xmm5
    3cac:	48 09 c2             	or     rdx,rax
    3caf:	48 8b 44 24 48       	mov    rax,QWORD PTR [rsp+0x48]
    3cb4:	0f 29 6c 24 70       	movaps XMMWORD PTR [rsp+0x70],xmm5
    3cb9:	48 89 54 24 40       	mov    QWORD PTR [rsp+0x40],rdx
    3cbe:	8b 93 e0 01 00 00    	mov    edx,DWORD PTR [rbx+0x1e0]
    3cc4:	48 21 e8             	and    rax,rbp
    3cc7:	0f 29 ac 24 80 00 00 	movaps XMMWORD PTR [rsp+0x80],xmm5
    3cce:	00 
    3ccf:	48 09 d0             	or     rax,rdx
    3cd2:	8b 93 c8 01 00 00    	mov    edx,DWORD PTR [rbx+0x1c8]
    3cd8:	89 c0                	mov    eax,eax
    3cda:	48 c1 e2 20          	shl    rdx,0x20
    3cde:	48 09 d0             	or     rax,rdx
    3ce1:	8b 93 b0 01 00 00    	mov    edx,DWORD PTR [rbx+0x1b0]
    3ce7:	48 89 44 24 48       	mov    QWORD PTR [rsp+0x48],rax
    3cec:	8b 83 98 01 00 00    	mov    eax,DWORD PTR [rbx+0x198]
    3cf2:	48 c1 e0 20          	shl    rax,0x20
    3cf6:	48 09 c2             	or     rdx,rax
    3cf9:	48 8b 44 24 58       	mov    rax,QWORD PTR [rsp+0x58]
    3cfe:	48 89 54 24 50       	mov    QWORD PTR [rsp+0x50],rdx
    3d03:	8b 93 80 01 00 00    	mov    edx,DWORD PTR [rbx+0x180]
    3d09:	48 21 e8             	and    rax,rbp
    3d0c:	48 09 d0             	or     rax,rdx
    3d0f:	8b 93 68 01 00 00    	mov    edx,DWORD PTR [rbx+0x168]
    3d15:	89 c0                	mov    eax,eax
    3d17:	48 c1 e2 20          	shl    rdx,0x20
    3d1b:	48 09 d0             	or     rax,rdx
    3d1e:	8b 93 50 01 00 00    	mov    edx,DWORD PTR [rbx+0x150]
    3d24:	48 89 44 24 58       	mov    QWORD PTR [rsp+0x58],rax
    3d29:	8b 83 38 01 00 00    	mov    eax,DWORD PTR [rbx+0x138]
    3d2f:	48 c1 e0 20          	shl    rax,0x20
    3d33:	48 09 c2             	or     rdx,rax
    3d36:	48 8b 44 24 68       	mov    rax,QWORD PTR [rsp+0x68]
    3d3b:	48 89 54 24 60       	mov    QWORD PTR [rsp+0x60],rdx
    3d40:	8b 93 20 01 00 00    	mov    edx,DWORD PTR [rbx+0x120]
    3d46:	48 21 e8             	and    rax,rbp
    3d49:	48 09 d0             	or     rax,rdx
    3d4c:	8b 93 08 01 00 00    	mov    edx,DWORD PTR [rbx+0x108]
    3d52:	89 c0                	mov    eax,eax
    3d54:	48 c1 e2 20          	shl    rdx,0x20
    3d58:	48 09 d0             	or     rax,rdx
    3d5b:	8b 93 f0 00 00 00    	mov    edx,DWORD PTR [rbx+0xf0]
    3d61:	48 89 44 24 68       	mov    QWORD PTR [rsp+0x68],rax
    3d66:	8b 83 d8 00 00 00    	mov    eax,DWORD PTR [rbx+0xd8]
    3d6c:	48 c1 e0 20          	shl    rax,0x20
    3d70:	48 09 c2             	or     rdx,rax
    3d73:	48 8b 44 24 78       	mov    rax,QWORD PTR [rsp+0x78]
    3d78:	48 89 54 24 70       	mov    QWORD PTR [rsp+0x70],rdx
    3d7d:	8b 93 c0 00 00 00    	mov    edx,DWORD PTR [rbx+0xc0]
    3d83:	48 21 e8             	and    rax,rbp
    3d86:	48 09 d0             	or     rax,rdx
    3d89:	8b 93 a8 00 00 00    	mov    edx,DWORD PTR [rbx+0xa8]
    3d8f:	89 c0                	mov    eax,eax
    3d91:	48 c1 e2 20          	shl    rdx,0x20
    3d95:	48 09 d0             	or     rax,rdx
    3d98:	48 89 44 24 78       	mov    QWORD PTR [rsp+0x78],rax
    3d9d:	8b 93 90 00 00 00    	mov    edx,DWORD PTR [rbx+0x90]
    3da3:	66 0f 66 4c 24 10    	pcmpgtd xmm1,XMMWORD PTR [rsp+0x10]
    3da9:	66 0f 6f 5c 24 10    	movdqa xmm3,XMMWORD PTR [rsp+0x10]
    3daf:	66 0f 6f 44 24 10    	movdqa xmm0,XMMWORD PTR [rsp+0x10]
    3db5:	66 0f 6f 24 24       	movdqa xmm4,XMMWORD PTR [rsp]
    3dba:	8b 43 78             	mov    eax,DWORD PTR [rbx+0x78]
    3dbd:	66 0f 62 d9          	punpckldq xmm3,xmm1
    3dc1:	66 0f 6a c1          	punpckhdq xmm0,xmm1
    3dc5:	66 0f 6f 0c 24       	movdqa xmm1,XMMWORD PTR [rsp]
    3dca:	66 0f eb c3          	por    xmm0,xmm3
    3dce:	66 0f 6f dd          	movdqa xmm3,xmm5
    3dd2:	48 c1 e0 20          	shl    rax,0x20
    3dd6:	66 0f 66 1c 24       	pcmpgtd xmm3,XMMWORD PTR [rsp]
    3ddb:	48 09 c2             	or     rdx,rax
    3dde:	48 8b 84 24 88 00 00 	mov    rax,QWORD PTR [rsp+0x88]
    3de5:	00 
    3de6:	48 89 94 24 80 00 00 	mov    QWORD PTR [rsp+0x80],rdx
    3ded:	00 
    3dee:	8b 53 60             	mov    edx,DWORD PTR [rbx+0x60]
    3df1:	48 21 e8             	and    rax,rbp
    3df4:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3df8:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3dfc:	66 0f 6f dd          	movdqa xmm3,xmm5
    3e00:	48 09 d0             	or     rax,rdx
    3e03:	66 0f 66 5c 24 20    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x20]
    3e09:	66 0f eb cc          	por    xmm1,xmm4
    3e0d:	8b 53 48             	mov    edx,DWORD PTR [rbx+0x48]
    3e10:	89 c0                	mov    eax,eax
    3e12:	66 0f 6f 64 24 20    	movdqa xmm4,XMMWORD PTR [rsp+0x20]
    3e18:	66 0f eb c1          	por    xmm0,xmm1
    3e1c:	66 0f 6f 4c 24 20    	movdqa xmm1,XMMWORD PTR [rsp+0x20]
    3e22:	48 c1 e2 20          	shl    rdx,0x20
    3e26:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3e2a:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3e2e:	66 0f 6f dd          	movdqa xmm3,xmm5
    3e32:	48 09 d0             	or     rax,rdx
    3e35:	66 0f 66 5c 24 30    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x30]
    3e3b:	66 0f eb cc          	por    xmm1,xmm4
    3e3f:	66 0f 6f 64 24 30    	movdqa xmm4,XMMWORD PTR [rsp+0x30]
    3e45:	48 89 84 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rax
    3e4c:	00 
    3e4d:	ba 00 08 00 00       	mov    edx,0x800
    3e52:	66 0f 66 94 24 80 00 	pcmpgtd xmm2,XMMWORD PTR [rsp+0x80]
    3e59:	00 00 
    3e5b:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3e5f:	66 0f eb cc          	por    xmm1,xmm4
    3e63:	66 0f 6f e5          	movdqa xmm4,xmm5
    3e67:	66 0f eb c1          	por    xmm0,xmm1
    3e6b:	66 0f 6f 4c 24 30    	movdqa xmm1,XMMWORD PTR [rsp+0x30]
    3e71:	66 0f 66 64 24 40    	pcmpgtd xmm4,XMMWORD PTR [rsp+0x40]
    3e77:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3e7b:	66 0f 6f 5c 24 40    	movdqa xmm3,XMMWORD PTR [rsp+0x40]
    3e81:	66 0f 62 dc          	punpckldq xmm3,xmm4
    3e85:	66 0f eb d9          	por    xmm3,xmm1
    3e89:	66 0f 6f 4c 24 40    	movdqa xmm1,XMMWORD PTR [rsp+0x40]
    3e8f:	66 0f 6a cc          	punpckhdq xmm1,xmm4
    3e93:	66 0f 6f 64 24 50    	movdqa xmm4,XMMWORD PTR [rsp+0x50]
    3e99:	66 0f eb cb          	por    xmm1,xmm3
    3e9d:	66 0f 6f dd          	movdqa xmm3,xmm5
    3ea1:	66 0f 66 5c 24 50    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x50]
    3ea7:	66 0f eb c1          	por    xmm0,xmm1
    3eab:	66 0f 6f 4c 24 50    	movdqa xmm1,XMMWORD PTR [rsp+0x50]
    3eb1:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3eb5:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3eb9:	66 0f 6f dd          	movdqa xmm3,xmm5
    3ebd:	66 0f 66 5c 24 60    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x60]
    3ec3:	66 0f eb cc          	por    xmm1,xmm4
    3ec7:	66 0f 6f 64 24 60    	movdqa xmm4,XMMWORD PTR [rsp+0x60]
    3ecd:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3ed1:	66 0f eb cc          	por    xmm1,xmm4
    3ed5:	66 0f 6f e5          	movdqa xmm4,xmm5
    3ed9:	66 0f eb c1          	por    xmm0,xmm1
    3edd:	66 0f 6f 4c 24 60    	movdqa xmm1,XMMWORD PTR [rsp+0x60]
    3ee3:	66 0f 66 64 24 70    	pcmpgtd xmm4,XMMWORD PTR [rsp+0x70]
    3ee9:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3eed:	66 0f 6f 5c 24 70    	movdqa xmm3,XMMWORD PTR [rsp+0x70]
    3ef3:	66 0f 62 dc          	punpckldq xmm3,xmm4
    3ef7:	66 0f eb d9          	por    xmm3,xmm1
    3efb:	66 0f 6f 4c 24 70    	movdqa xmm1,XMMWORD PTR [rsp+0x70]
    3f01:	66 0f 6a cc          	punpckhdq xmm1,xmm4
    3f05:	66 0f eb cb          	por    xmm1,xmm3
    3f09:	66 0f 6f 9c 24 80 00 	movdqa xmm3,XMMWORD PTR [rsp+0x80]
    3f10:	00 00 
    3f12:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
    3f15:	66 0f eb c1          	por    xmm0,xmm1
    3f19:	49 8b 7d 00          	mov    rdi,QWORD PTR [r13+0x0]
    3f1d:	66 0f 6f 8c 24 80 00 	movdqa xmm1,XMMWORD PTR [rsp+0x80]
    3f24:	00 00 
    3f26:	66 0f 62 da          	punpckldq xmm3,xmm2
    3f2a:	66 0f 6a ca          	punpckhdq xmm1,xmm2
    3f2e:	66 0f eb cb          	por    xmm1,xmm3
    3f32:	66 0f eb c1          	por    xmm0,xmm1
    3f36:	66 0f 6f c8          	movdqa xmm1,xmm0
    3f3a:	66 0f 73 d9 08       	psrldq xmm1,0x8
    3f3f:	66 0f eb c1          	por    xmm0,xmm1
    3f43:	66 0f d6 84 24 d8 00 	movq   QWORD PTR [rsp+0xd8],xmm0
    3f4a:	00 00 
    3f4c:	e8 3f e4 ff ff       	call   2390 <XChangeWindowAttributes@plt>
    3f51:	48 8b 5b 10          	mov    rbx,QWORD PTR [rbx+0x10]
    3f55:	48 85 db             	test   rbx,rbx
    3f58:	0f 85 1a fc ff ff    	jne    3b78 <mlx_int_set_win_event_mask+0x48>
    3f5e:	48 8b 84 24 08 01 00 	mov    rax,QWORD PTR [rsp+0x108]
    3f65:	00 
    3f66:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3f6d:	00 00 
    3f6f:	75 10                	jne    3f81 <mlx_int_set_win_event_mask+0x451>
    3f71:	48 81 c4 18 01 00 00 	add    rsp,0x118
    3f78:	31 c0                	xor    eax,eax
    3f7a:	5b                   	pop    rbx
    3f7b:	5d                   	pop    rbp
    3f7c:	41 5c                	pop    r12
    3f7e:	41 5d                	pop    r13
    3f80:	c3                   	ret
    3f81:	e8 ea e2 ff ff       	call   2270 <__stack_chk_fail@plt>
    3f86:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    3f8d:	00 00 00 

0000000000003f90 <mlx_hook>:
    3f90:	48 63 f6             	movsxd rsi,esi
    3f93:	48 8d 04 76          	lea    rax,[rsi+rsi*2]
    3f97:	48 8d 04 c7          	lea    rax,[rdi+rax*8]
    3f9b:	48 89 48 50          	mov    QWORD PTR [rax+0x50],rcx
    3f9f:	4c 89 40 58          	mov    QWORD PTR [rax+0x58],r8
    3fa3:	89 50 48             	mov    DWORD PTR [rax+0x48],edx
    3fa6:	c3                   	ret
    3fa7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    3fae:	00 00 

0000000000003fb0 <mlx_do_key_autorepeatoff>:
    3fb0:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3fb3:	e9 d8 e0 ff ff       	jmp    2090 <XAutoRepeatOff@plt>
    3fb8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    3fbf:	00 

0000000000003fc0 <mlx_do_key_autorepeaton>:
    3fc0:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3fc3:	e9 68 e1 ff ff       	jmp    2130 <XAutoRepeatOn@plt>
    3fc8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    3fcf:	00 

0000000000003fd0 <mlx_do_sync>:
    3fd0:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3fd3:	31 f6                	xor    esi,esi
    3fd5:	e9 86 e2 ff ff       	jmp    2260 <XSync@plt>
    3fda:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000003fe0 <mlx_destroy_display>:
    3fe0:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3fe3:	e9 a8 e1 ff ff       	jmp    2190 <XCloseDisplay@plt>
