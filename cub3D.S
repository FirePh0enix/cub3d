
cub3D:     file format elf64-x86-64


Disassembly of section .text:

0000000000002370 <_start>:
    2370:	f3 0f 1e fa          	endbr64
    2374:	31 ed                	xor    ebp,ebp
    2376:	49 89 d1             	mov    r9,rdx
    2379:	5e                   	pop    rsi
    237a:	48 89 e2             	mov    rdx,rsp
    237d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    2381:	50                   	push   rax
    2382:	54                   	push   rsp
    2383:	45 31 c0             	xor    r8d,r8d
    2386:	31 c9                	xor    ecx,ecx
    2388:	48 8d 3d e1 00 00 00 	lea    rdi,[rip+0xe1]        # 2470 <main>
    238f:	ff 15 4b 3c 00 00    	call   QWORD PTR [rip+0x3c4b]        # 5fe0 <__libc_start_main@GLIBC_2.34>
    2395:	f4                   	hlt
    2396:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    239d:	00 00 00 
    23a0:	48 8d 3d 39 3f 00 00 	lea    rdi,[rip+0x3f39]        # 62e0 <__TMC_END__>
    23a7:	48 8d 05 32 3f 00 00 	lea    rax,[rip+0x3f32]        # 62e0 <__TMC_END__>
    23ae:	48 39 f8             	cmp    rax,rdi
    23b1:	74 15                	je     23c8 <_start+0x58>
    23b3:	48 8b 05 0e 3c 00 00 	mov    rax,QWORD PTR [rip+0x3c0e]        # 5fc8 <_ITM_deregisterTMCloneTable@Base>
    23ba:	48 85 c0             	test   rax,rax
    23bd:	74 09                	je     23c8 <_start+0x58>
    23bf:	ff e0                	jmp    rax
    23c1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    23c8:	c3                   	ret
    23c9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    23d0:	48 8d 3d 09 3f 00 00 	lea    rdi,[rip+0x3f09]        # 62e0 <__TMC_END__>
    23d7:	48 8d 35 02 3f 00 00 	lea    rsi,[rip+0x3f02]        # 62e0 <__TMC_END__>
    23de:	48 29 fe             	sub    rsi,rdi
    23e1:	48 89 f0             	mov    rax,rsi
    23e4:	48 c1 ee 3f          	shr    rsi,0x3f
    23e8:	48 c1 f8 03          	sar    rax,0x3
    23ec:	48 01 c6             	add    rsi,rax
    23ef:	48 d1 fe             	sar    rsi,1
    23f2:	74 14                	je     2408 <_start+0x98>
    23f4:	48 8b 05 d5 3b 00 00 	mov    rax,QWORD PTR [rip+0x3bd5]        # 5fd0 <_ITM_registerTMCloneTable@Base>
    23fb:	48 85 c0             	test   rax,rax
    23fe:	74 08                	je     2408 <_start+0x98>
    2400:	ff e0                	jmp    rax
    2402:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2408:	c3                   	ret
    2409:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2410:	f3 0f 1e fa          	endbr64
    2414:	80 3d c5 3e 00 00 00 	cmp    BYTE PTR [rip+0x3ec5],0x0        # 62e0 <__TMC_END__>
    241b:	75 33                	jne    2450 <_start+0xe0>
    241d:	55                   	push   rbp
    241e:	48 83 3d b2 3b 00 00 	cmp    QWORD PTR [rip+0x3bb2],0x0        # 5fd8 <__cxa_finalize@GLIBC_2.2.5>
    2425:	00 
    2426:	48 89 e5             	mov    rbp,rsp
    2429:	74 0d                	je     2438 <_start+0xc8>
    242b:	48 8b 3d 76 3d 00 00 	mov    rdi,QWORD PTR [rip+0x3d76]        # 61a8 <__dso_handle>
    2432:	ff 15 a0 3b 00 00    	call   QWORD PTR [rip+0x3ba0]        # 5fd8 <__cxa_finalize@GLIBC_2.2.5>
    2438:	e8 63 ff ff ff       	call   23a0 <_start+0x30>
    243d:	c6 05 9c 3e 00 00 01 	mov    BYTE PTR [rip+0x3e9c],0x1        # 62e0 <__TMC_END__>
    2444:	5d                   	pop    rbp
    2445:	c3                   	ret
    2446:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    244d:	00 00 00 
    2450:	c3                   	ret
    2451:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    2458:	00 00 00 00 
    245c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    2460:	f3 0f 1e fa          	endbr64
    2464:	e9 67 ff ff ff       	jmp    23d0 <_start+0x60>
    2469:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000002470 <main>:
    2470:	41 57                	push   r15
    2472:	41 56                	push   r14
    2474:	53                   	push   rbx
    2475:	48 81 ec e0 00 00 00 	sub    rsp,0xe0
    247c:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2483:	00 00 
    2485:	48 89 84 24 d8 00 00 	mov    QWORD PTR [rsp+0xd8],rax
    248c:	00 
    248d:	48 8d 35 7c 1b 00 00 	lea    rsi,[rip+0x1b7c]        # 4010 <_IO_stdin_used+0x10>
    2494:	4c 8d 7c 24 40       	lea    r15,[rsp+0x40]
    2499:	ba 90 00 00 00       	mov    edx,0x90
    249e:	4c 89 ff             	mov    rdi,r15
    24a1:	e8 8a fe ff ff       	call   2330 <memcpy@plt>
    24a6:	31 c0                	xor    eax,eax
    24a8:	e8 73 04 00 00       	call   2920 <mlx_init>
    24ad:	48 89 c3             	mov    rbx,rax
    24b0:	48 8d 0d e9 1b 00 00 	lea    rcx,[rip+0x1be9]        # 40a0 <_IO_stdin_used+0xa0>
    24b7:	48 89 c7             	mov    rdi,rax
    24ba:	be 00 05 00 00       	mov    esi,0x500
    24bf:	ba d0 02 00 00       	mov    edx,0x2d0
    24c4:	e8 97 05 00 00       	call   2a60 <mlx_new_window>
    24c9:	49 89 c6             	mov    r14,rax
    24cc:	be 03 00 00 00       	mov    esi,0x3
    24d1:	4c 89 ff             	mov    rdi,r15
    24d4:	e8 b7 01 00 00       	call   2690 <mesh_load_from_data>
    24d9:	48 8d 0d 90 00 00 00 	lea    rcx,[rip+0x90]        # 2570 <close_hook>
    24e0:	4c 89 f7             	mov    rdi,r14
    24e3:	be 11 00 00 00       	mov    esi,0x11
    24e8:	31 d2                	xor    edx,edx
    24ea:	49 89 d8             	mov    r8,rbx
    24ed:	e8 2e 16 00 00       	call   3b20 <mlx_hook>
    24f2:	48 89 e7             	mov    rdi,rsp
    24f5:	48 89 de             	mov    rsi,rbx
    24f8:	ba 00 05 00 00       	mov    edx,0x500
    24fd:	b9 d0 02 00 00       	mov    ecx,0x2d0
    2502:	e8 79 00 00 00       	call   2580 <r3d_init>
    2507:	48 8b 14 24          	mov    rdx,QWORD PTR [rsp]
    250b:	48 89 df             	mov    rdi,rbx
    250e:	4c 89 f6             	mov    rsi,r14
    2511:	31 c9                	xor    ecx,ecx
    2513:	45 31 c0             	xor    r8d,r8d
    2516:	e8 25 0e 00 00       	call   3340 <mlx_put_image_to_window>
    251b:	48 89 df             	mov    rdi,rbx
    251e:	e8 ad 06 00 00       	call   2bd0 <mlx_loop>
    2523:	48 89 df             	mov    rdi,rbx
    2526:	4c 89 f6             	mov    rsi,r14
    2529:	e8 52 0f 00 00       	call   3480 <mlx_destroy_window>
    252e:	48 89 df             	mov    rdi,rbx
    2531:	e8 3a 16 00 00       	call   3b70 <mlx_destroy_display>
    2536:	48 89 df             	mov    rdi,rbx
    2539:	e8 f2 fb ff ff       	call   2130 <free@plt>
    253e:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2545:	00 00 
    2547:	48 3b 84 24 d8 00 00 	cmp    rax,QWORD PTR [rsp+0xd8]
    254e:	00 
    254f:	75 0f                	jne    2560 <main+0xf0>
    2551:	31 c0                	xor    eax,eax
    2553:	48 81 c4 e0 00 00 00 	add    rsp,0xe0
    255a:	5b                   	pop    rbx
    255b:	41 5e                	pop    r14
    255d:	41 5f                	pop    r15
    255f:	c3                   	ret
    2560:	e8 db fc ff ff       	call   2240 <__stack_chk_fail@plt>
    2565:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    256c:	00 00 00 00 

0000000000002570 <close_hook>:
    2570:	e9 4b 06 00 00       	jmp    2bc0 <mlx_loop_end>
    2575:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    257c:	00 00 00 
    257f:	90                   	nop

0000000000002580 <r3d_init>:
    2580:	55                   	push   rbp
    2581:	41 57                	push   r15
    2583:	41 56                	push   r14
    2585:	53                   	push   rbx
    2586:	50                   	push   rax
    2587:	89 cb                	mov    ebx,ecx
    2589:	89 d5                	mov    ebp,edx
    258b:	49 89 fe             	mov    r14,rdi
    258e:	48 89 f7             	mov    rdi,rsi
    2591:	89 d6                	mov    esi,edx
    2593:	89 ca                	mov    edx,ecx
    2595:	e8 06 0d 00 00       	call   32a0 <mlx_new_image>
    259a:	49 89 06             	mov    QWORD PTR [r14],rax
    259d:	48 8b 40 30          	mov    rax,QWORD PTR [rax+0x30]
    25a1:	49 89 46 30          	mov    QWORD PTR [r14+0x30],rax
    25a5:	4c 63 fd             	movsxd r15,ebp
    25a8:	48 63 db             	movsxd rbx,ebx
    25ab:	4c 89 ff             	mov    rdi,r15
    25ae:	48 0f af fb          	imul   rdi,rbx
    25b2:	48 c1 e7 02          	shl    rdi,0x2
    25b6:	e8 05 fb ff ff       	call   20c0 <malloc@plt>
    25bb:	49 89 46 38          	mov    QWORD PTR [r14+0x38],rax
    25bf:	45 89 7e 08          	mov    DWORD PTR [r14+0x8],r15d
    25c3:	41 89 5e 0c          	mov    DWORD PTR [r14+0xc],ebx
    25c7:	0f 57 c0             	xorps  xmm0,xmm0
    25ca:	41 0f 13 46 20       	movlps QWORD PTR [r14+0x20],xmm0
    25cf:	41 c7 46 28 00 00 00 	mov    DWORD PTR [r14+0x28],0x0
    25d6:	00 
    25d7:	41 c7 46 10 7b 14 4e 	mov    DWORD PTR [r14+0x10],0x424e147b
    25de:	42 
    25df:	48 83 c4 08          	add    rsp,0x8
    25e3:	5b                   	pop    rbx
    25e4:	41 5e                	pop    r14
    25e6:	41 5f                	pop    r15
    25e8:	5d                   	pop    rbp
    25e9:	c3                   	ret
    25ea:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000000025f0 <r3d_clear_depth_buffer>:
    25f0:	8b 57 0c             	mov    edx,DWORD PTR [rdi+0xc]
    25f3:	0f af 57 08          	imul   edx,DWORD PTR [rdi+0x8]
    25f7:	85 d2                	test   edx,edx
    25f9:	7e 54                	jle    264f <r3d_clear_depth_buffer+0x5f>
    25fb:	48 8b 47 38          	mov    rax,QWORD PTR [rdi+0x38]
    25ff:	89 d1                	mov    ecx,edx
    2601:	83 fa 08             	cmp    edx,0x8
    2604:	73 04                	jae    260a <r3d_clear_depth_buffer+0x1a>
    2606:	31 d2                	xor    edx,edx
    2608:	eb 36                	jmp    2640 <r3d_clear_depth_buffer+0x50>
    260a:	89 ca                	mov    edx,ecx
    260c:	83 e2 f8             	and    edx,0xfffffff8
    260f:	31 f6                	xor    esi,esi
    2611:	0f 28 05 c8 1a 00 00 	movaps xmm0,XMMWORD PTR [rip+0x1ac8]        # 40e0 <_IO_stdin_used+0xe0>
    2618:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    261f:	00 
    2620:	0f 11 04 b0          	movups XMMWORD PTR [rax+rsi*4],xmm0
    2624:	0f 11 44 b0 10       	movups XMMWORD PTR [rax+rsi*4+0x10],xmm0
    2629:	48 83 c6 08          	add    rsi,0x8
    262d:	48 39 f2             	cmp    rdx,rsi
    2630:	75 ee                	jne    2620 <r3d_clear_depth_buffer+0x30>
    2632:	48 39 ca             	cmp    rdx,rcx
    2635:	74 18                	je     264f <r3d_clear_depth_buffer+0x5f>
    2637:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    263e:	00 00 
    2640:	c7 04 90 00 00 80 7f 	mov    DWORD PTR [rax+rdx*4],0x7f800000
    2647:	48 ff c2             	inc    rdx
    264a:	48 39 d1             	cmp    rcx,rdx
    264d:	75 f1                	jne    2640 <r3d_clear_depth_buffer+0x50>
    264f:	c3                   	ret

0000000000002650 <r3d_clear_color_buffer>:
    2650:	8b 47 0c             	mov    eax,DWORD PTR [rdi+0xc]
    2653:	0f af 47 08          	imul   eax,DWORD PTR [rdi+0x8]
    2657:	85 c0                	test   eax,eax
    2659:	7e 2c                	jle    2687 <r3d_clear_color_buffer+0x37>
    265b:	48 8b 47 30          	mov    rax,QWORD PTR [rdi+0x30]
    265f:	31 c9                	xor    ecx,ecx
    2661:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]
    2668:	0f 1f 84 00 00 00 00 
    266f:	00 
    2670:	89 34 88             	mov    DWORD PTR [rax+rcx*4],esi
    2673:	48 ff c1             	inc    rcx
    2676:	48 63 57 08          	movsxd rdx,DWORD PTR [rdi+0x8]
    267a:	4c 63 47 0c          	movsxd r8,DWORD PTR [rdi+0xc]
    267e:	4c 0f af c2          	imul   r8,rdx
    2682:	4c 39 c1             	cmp    rcx,r8
    2685:	7c e9                	jl     2670 <r3d_clear_color_buffer+0x20>
    2687:	c3                   	ret
    2688:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    268f:	00 

0000000000002690 <mesh_load_from_data>:
    2690:	41 57                	push   r15
    2692:	41 56                	push   r14
    2694:	53                   	push   rbx
    2695:	49 89 f7             	mov    r15,rsi
    2698:	48 89 fb             	mov    rbx,rdi
    269b:	bf 10 00 00 00       	mov    edi,0x10
    26a0:	e8 1b fa ff ff       	call   20c0 <malloc@plt>
    26a5:	49 89 c6             	mov    r14,rax
    26a8:	4c 89 78 08          	mov    QWORD PTR [rax+0x8],r15
    26ac:	4c 89 ff             	mov    rdi,r15
    26af:	48 c1 e7 04          	shl    rdi,0x4
    26b3:	e8 08 fa ff ff       	call   20c0 <malloc@plt>
    26b8:	49 89 06             	mov    QWORD PTR [r14],rax
    26bb:	4d 85 ff             	test   r15,r15
    26be:	74 51                	je     2711 <mesh_load_from_data+0x81>
    26c0:	49 83 ff 01          	cmp    r15,0x1
    26c4:	75 04                	jne    26ca <mesh_load_from_data+0x3a>
    26c6:	31 c9                	xor    ecx,ecx
    26c8:	eb 35                	jmp    26ff <mesh_load_from_data+0x6f>
    26ca:	4c 89 fa             	mov    rdx,r15
    26cd:	48 83 e2 fe          	and    rdx,0xfffffffffffffffe
    26d1:	be 10 00 00 00       	mov    esi,0x10
    26d6:	31 c9                	xor    ecx,ecx
    26d8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    26df:	00 
    26e0:	0f 28 44 33 f0       	movaps xmm0,XMMWORD PTR [rbx+rsi*1-0x10]
    26e5:	0f 29 44 30 f0       	movaps XMMWORD PTR [rax+rsi*1-0x10],xmm0
    26ea:	0f 28 04 33          	movaps xmm0,XMMWORD PTR [rbx+rsi*1]
    26ee:	0f 29 04 30          	movaps XMMWORD PTR [rax+rsi*1],xmm0
    26f2:	48 83 c1 02          	add    rcx,0x2
    26f6:	48 83 c6 20          	add    rsi,0x20
    26fa:	48 39 ca             	cmp    rdx,rcx
    26fd:	75 e1                	jne    26e0 <mesh_load_from_data+0x50>
    26ff:	41 f6 c7 01          	test   r15b,0x1
    2703:	74 0c                	je     2711 <mesh_load_from_data+0x81>
    2705:	48 c1 e1 04          	shl    rcx,0x4
    2709:	0f 28 04 0b          	movaps xmm0,XMMWORD PTR [rbx+rcx*1]
    270d:	0f 29 04 08          	movaps XMMWORD PTR [rax+rcx*1],xmm0
    2711:	4c 89 f0             	mov    rax,r14
    2714:	5b                   	pop    rbx
    2715:	41 5e                	pop    r14
    2717:	41 5f                	pop    r15
    2719:	c3                   	ret
    271a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000002720 <mesh_destroy>:
    2720:	53                   	push   rbx
    2721:	48 89 fb             	mov    rbx,rdi
    2724:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    2727:	e8 04 fa ff ff       	call   2130 <free@plt>
    272c:	48 89 df             	mov    rdi,rbx
    272f:	5b                   	pop    rbx
    2730:	e9 fb f9 ff ff       	jmp    2130 <free@plt>
    2735:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    273c:	00 00 00 
    273f:	90                   	nop

0000000000002740 <r3d_draw_mesh>:
    2740:	c3                   	ret
    2741:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    2748:	00 00 00 
    274b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000002750 <mlx_int_deal_shm>:
    2750:	41 54                	push   r12
    2752:	55                   	push   rbp
    2753:	53                   	push   rbx
    2754:	48 89 fb             	mov    rbx,rdi
    2757:	48 83 ec 40          	sub    rsp,0x40
    275b:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    275e:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2765:	00 00 
    2767:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
    276c:	31 c0                	xor    eax,eax
    276e:	48 8d 74 24 0c       	lea    rsi,[rsp+0xc]
    2773:	48 8d 4c 24 08       	lea    rcx,[rsp+0x8]
    2778:	48 89 f2             	mov    rdx,rsi
    277b:	e8 20 fa ff ff       	call   21a0 <XShmQueryVersion@plt>
    2780:	ba ff ff ff ff       	mov    edx,0xffffffff
    2785:	89 43 48             	mov    DWORD PTR [rbx+0x48],eax
    2788:	85 c0                	test   eax,eax
    278a:	74 0c                	je     2798 <mlx_int_deal_shm+0x48>
    278c:	8b 44 24 08          	mov    eax,DWORD PTR [rsp+0x8]
    2790:	85 c0                	test   eax,eax
    2792:	0f 85 98 00 00 00    	jne    2830 <mlx_int_deal_shm+0xe0>
    2798:	89 53 4c             	mov    DWORD PTR [rbx+0x4c],edx
    279b:	4c 8d 64 24 10       	lea    r12,[rsp+0x10]
    27a0:	be 20 00 00 00       	mov    esi,0x20
    27a5:	4c 89 e7             	mov    rdi,r12
    27a8:	e8 33 fa ff ff       	call   21e0 <gethostname@plt>
    27ad:	48 8d 3d f2 18 00 00 	lea    rdi,[rip+0x18f2]        # 40a6 <_IO_stdin_used+0xa6>
    27b4:	e8 57 fa ff ff       	call   2210 <getenv@plt>
    27b9:	48 89 c5             	mov    rbp,rax
    27bc:	48 85 c0             	test   rax,rax
    27bf:	74 4f                	je     2810 <mlx_int_deal_shm+0xc0>
    27c1:	0f b6 00             	movzx  eax,BYTE PTR [rax]
    27c4:	3c 3a                	cmp    al,0x3a
    27c6:	74 48                	je     2810 <mlx_int_deal_shm+0xc0>
    27c8:	84 c0                	test   al,al
    27ca:	74 44                	je     2810 <mlx_int_deal_shm+0xc0>
    27cc:	4c 89 e7             	mov    rdi,r12
    27cf:	e8 7c f9 ff ff       	call   2150 <strlen@plt>
    27d4:	4c 89 e6             	mov    rsi,r12
    27d7:	48 89 ef             	mov    rdi,rbp
    27da:	48 89 c2             	mov    rdx,rax
    27dd:	e8 ce f8 ff ff       	call   20b0 <strncmp@plt>
    27e2:	85 c0                	test   eax,eax
    27e4:	74 2a                	je     2810 <mlx_int_deal_shm+0xc0>
    27e6:	ba 09 00 00 00       	mov    edx,0x9
    27eb:	48 8d 35 bc 18 00 00 	lea    rsi,[rip+0x18bc]        # 40ae <_IO_stdin_used+0xae>
    27f2:	48 89 ef             	mov    rdi,rbp
    27f5:	e8 b6 f8 ff ff       	call   20b0 <strncmp@plt>
    27fa:	85 c0                	test   eax,eax
    27fc:	74 12                	je     2810 <mlx_int_deal_shm+0xc0>
    27fe:	48 8b 05 5b 19 00 00 	mov    rax,QWORD PTR [rip+0x195b]        # 4160 <_IO_stdin_used+0x160>
    2805:	48 89 43 48          	mov    QWORD PTR [rbx+0x48],rax
    2809:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2810:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
    2815:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    281c:	00 00 
    281e:	75 1f                	jne    283f <mlx_int_deal_shm+0xef>
    2820:	48 83 c4 40          	add    rsp,0x40
    2824:	31 c0                	xor    eax,eax
    2826:	5b                   	pop    rbx
    2827:	5d                   	pop    rbp
    2828:	41 5c                	pop    r12
    282a:	c3                   	ret
    282b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    2830:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2833:	e8 c8 fa ff ff       	call   2300 <XShmPixmapFormat@plt>
    2838:	89 c2                	mov    edx,eax
    283a:	e9 59 ff ff ff       	jmp    2798 <mlx_int_deal_shm+0x48>
    283f:	e8 fc f9 ff ff       	call   2240 <__stack_chk_fail@plt>
    2844:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    284b:	00 00 00 00 
    284f:	90                   	nop

0000000000002850 <mlx_int_rgb_conversion>:
    2850:	48 8b 77 18          	mov    rsi,QWORD PTR [rdi+0x18]
    2854:	66 0f ef c0          	pxor   xmm0,xmm0
    2858:	48 c7 47 64 00 00 00 	mov    QWORD PTR [rdi+0x64],0x0
    285f:	00 
    2860:	0f 11 47 54          	movups XMMWORD PTR [rdi+0x54],xmm0
    2864:	48 8b 46 18          	mov    rax,QWORD PTR [rsi+0x18]
    2868:	a8 01                	test   al,0x1
    286a:	75 1b                	jne    2887 <mlx_int_rgb_conversion+0x37>
    286c:	ba 01 00 00 00       	mov    edx,0x1
    2871:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2878:	48 d1 e8             	shr    rax,1
    287b:	89 d1                	mov    ecx,edx
    287d:	83 c2 01             	add    edx,0x1
    2880:	a8 01                	test   al,0x1
    2882:	74 f4                	je     2878 <mlx_int_rgb_conversion+0x28>
    2884:	89 4f 54             	mov    DWORD PTR [rdi+0x54],ecx
    2887:	ba 01 00 00 00       	mov    edx,0x1
    288c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    2890:	48 d1 e8             	shr    rax,1
    2893:	89 d1                	mov    ecx,edx
    2895:	83 c2 01             	add    edx,0x1
    2898:	a8 01                	test   al,0x1
    289a:	75 f4                	jne    2890 <mlx_int_rgb_conversion+0x40>
    289c:	48 89 46 18          	mov    QWORD PTR [rsi+0x18],rax
    28a0:	48 8b 46 20          	mov    rax,QWORD PTR [rsi+0x20]
    28a4:	89 4f 58             	mov    DWORD PTR [rdi+0x58],ecx
    28a7:	a8 01                	test   al,0x1
    28a9:	75 12                	jne    28bd <mlx_int_rgb_conversion+0x6d>
    28ab:	31 d2                	xor    edx,edx
    28ad:	0f 1f 00             	nop    DWORD PTR [rax]
    28b0:	48 d1 e8             	shr    rax,1
    28b3:	83 c2 01             	add    edx,0x1
    28b6:	a8 01                	test   al,0x1
    28b8:	74 f6                	je     28b0 <mlx_int_rgb_conversion+0x60>
    28ba:	89 57 5c             	mov    DWORD PTR [rdi+0x5c],edx
    28bd:	ba 01 00 00 00       	mov    edx,0x1
    28c2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    28c8:	48 d1 e8             	shr    rax,1
    28cb:	89 d1                	mov    ecx,edx
    28cd:	83 c2 01             	add    edx,0x1
    28d0:	a8 01                	test   al,0x1
    28d2:	75 f4                	jne    28c8 <mlx_int_rgb_conversion+0x78>
    28d4:	48 89 46 20          	mov    QWORD PTR [rsi+0x20],rax
    28d8:	48 8b 46 28          	mov    rax,QWORD PTR [rsi+0x28]
    28dc:	89 4f 60             	mov    DWORD PTR [rdi+0x60],ecx
    28df:	a8 01                	test   al,0x1
    28e1:	75 12                	jne    28f5 <mlx_int_rgb_conversion+0xa5>
    28e3:	31 d2                	xor    edx,edx
    28e5:	0f 1f 00             	nop    DWORD PTR [rax]
    28e8:	48 d1 e8             	shr    rax,1
    28eb:	83 c2 01             	add    edx,0x1
    28ee:	a8 01                	test   al,0x1
    28f0:	74 f6                	je     28e8 <mlx_int_rgb_conversion+0x98>
    28f2:	89 57 64             	mov    DWORD PTR [rdi+0x64],edx
    28f5:	ba 01 00 00 00       	mov    edx,0x1
    28fa:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2900:	48 d1 e8             	shr    rax,1
    2903:	89 d1                	mov    ecx,edx
    2905:	83 c2 01             	add    edx,0x1
    2908:	a8 01                	test   al,0x1
    290a:	75 f4                	jne    2900 <mlx_int_rgb_conversion+0xb0>
    290c:	48 89 46 28          	mov    QWORD PTR [rsi+0x28],rax
    2910:	89 4f 68             	mov    DWORD PTR [rdi+0x68],ecx
    2913:	c3                   	ret
    2914:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    291b:	00 00 00 00 
    291f:	90                   	nop

0000000000002920 <mlx_init>:
    2920:	53                   	push   rbx
    2921:	bf 88 00 00 00       	mov    edi,0x88
    2926:	e8 95 f7 ff ff       	call   20c0 <malloc@plt>
    292b:	48 85 c0             	test   rax,rax
    292e:	0f 84 04 01 00 00    	je     2a38 <mlx_init+0x118>
    2934:	48 8d 3d 9a 17 00 00 	lea    rdi,[rip+0x179a]        # 40d5 <_IO_stdin_used+0xd5>
    293b:	48 89 c3             	mov    rbx,rax
    293e:	e8 dd f7 ff ff       	call   2120 <XOpenDisplay@plt>
    2943:	48 89 03             	mov    QWORD PTR [rbx],rax
    2946:	48 89 c2             	mov    rdx,rax
    2949:	48 85 c0             	test   rax,rax
    294c:	0f 84 de 00 00 00    	je     2a30 <mlx_init+0x110>
    2952:	48 63 80 e0 00 00 00 	movsxd rax,DWORD PTR [rax+0xe0]
    2959:	48 89 df             	mov    rdi,rbx
    295c:	48 89 c1             	mov    rcx,rax
    295f:	48 c1 e0 07          	shl    rax,0x7
    2963:	48 03 82 e8 00 00 00 	add    rax,QWORD PTR [rdx+0xe8]
    296a:	48 8b 50 10          	mov    rdx,QWORD PTR [rax+0x10]
    296e:	66 0f 6e 40 38       	movd   xmm0,DWORD PTR [rax+0x38]
    2973:	66 0f 6e c9          	movd   xmm1,ecx
    2977:	48 89 53 08          	mov    QWORD PTR [rbx+0x8],rdx
    297b:	48 8b 50 50          	mov    rdx,QWORD PTR [rax+0x50]
    297f:	66 0f 62 c8          	punpckldq xmm1,xmm0
    2983:	66 0f d6 4b 10       	movq   QWORD PTR [rbx+0x10],xmm1
    2988:	48 89 53 20          	mov    QWORD PTR [rbx+0x20],rdx
    298c:	e8 df 04 00 00       	call   2e70 <mlx_int_get_visual>
    2991:	83 f8 ff             	cmp    eax,0xffffffff
    2994:	0f 84 a2 00 00 00    	je     2a3c <mlx_init+0x11c>
    299a:	48 c7 43 30 00 00 00 	mov    QWORD PTR [rbx+0x30],0x0
    29a1:	00 
    29a2:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    29a5:	31 d2                	xor    edx,edx
    29a7:	48 8d 35 0a 17 00 00 	lea    rsi,[rip+0x170a]        # 40b8 <_IO_stdin_used+0xb8>
    29ae:	48 c7 43 38 00 00 00 	mov    QWORD PTR [rbx+0x38],0x0
    29b5:	00 
    29b6:	48 c7 43 40 00 00 00 	mov    QWORD PTR [rbx+0x40],0x0
    29bd:	00 
    29be:	c7 43 50 01 00 00 00 	mov    DWORD PTR [rbx+0x50],0x1
    29c5:	e8 c6 f8 ff ff       	call   2290 <XInternAtom@plt>
    29ca:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    29cd:	31 d2                	xor    edx,edx
    29cf:	48 8d 35 f3 16 00 00 	lea    rsi,[rip+0x16f3]        # 40c9 <_IO_stdin_used+0xc9>
    29d6:	48 89 43 70          	mov    QWORD PTR [rbx+0x70],rax
    29da:	e8 b1 f8 ff ff       	call   2290 <XInternAtom@plt>
    29df:	48 89 df             	mov    rdi,rbx
    29e2:	48 89 43 78          	mov    QWORD PTR [rbx+0x78],rax
    29e6:	31 c0                	xor    eax,eax
    29e8:	e8 63 fd ff ff       	call   2750 <mlx_int_deal_shm>
    29ed:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    29f0:	85 c0                	test   eax,eax
    29f2:	75 1c                	jne    2a10 <mlx_init+0xf0>
    29f4:	48 89 df             	mov    rdi,rbx
    29f7:	31 c0                	xor    eax,eax
    29f9:	e8 52 fe ff ff       	call   2850 <mlx_int_rgb_conversion>
    29fe:	c7 83 80 00 00 00 00 	mov    DWORD PTR [rbx+0x80],0x0
    2a05:	00 00 00 
    2a08:	48 89 d8             	mov    rax,rbx
    2a0b:	5b                   	pop    rbx
    2a0c:	c3                   	ret
    2a0d:	0f 1f 00             	nop    DWORD PTR [rax]
    2a10:	48 8b 53 18          	mov    rdx,QWORD PTR [rbx+0x18]
    2a14:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    2a18:	31 c9                	xor    ecx,ecx
    2a1a:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2a1d:	e8 de f6 ff ff       	call   2100 <XCreateColormap@plt>
    2a22:	48 89 43 20          	mov    QWORD PTR [rbx+0x20],rax
    2a26:	eb cc                	jmp    29f4 <mlx_init+0xd4>
    2a28:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    2a2f:	00 
    2a30:	48 89 df             	mov    rdi,rbx
    2a33:	e8 f8 f6 ff ff       	call   2130 <free@plt>
    2a38:	31 db                	xor    ebx,ebx
    2a3a:	eb cc                	jmp    2a08 <mlx_init+0xe8>
    2a3c:	48 8d 3d ad 16 00 00 	lea    rdi,[rip+0x16ad]        # 40f0 <_IO_stdin_used+0xf0>
    2a43:	e8 18 f6 ff ff       	call   2060 <puts@plt>
    2a48:	bf 01 00 00 00       	mov    edi,0x1
    2a4d:	e8 2e f6 ff ff       	call   2080 <exit@plt>
    2a52:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    2a59:	00 00 00 
    2a5c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000002a60 <mlx_new_window>:
    2a60:	41 56                	push   r14
    2a62:	49 89 ce             	mov    r14,rcx
    2a65:	41 55                	push   r13
    2a67:	41 89 d5             	mov    r13d,edx
    2a6a:	41 54                	push   r12
    2a6c:	41 89 f4             	mov    r12d,esi
    2a6f:	55                   	push   rbp
    2a70:	53                   	push   rbx
    2a71:	48 89 fb             	mov    rbx,rdi
    2a74:	48 81 ec 00 01 00 00 	sub    rsp,0x100
    2a7b:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2a82:	00 00 
    2a84:	48 89 84 24 f8 00 00 	mov    QWORD PTR [rsp+0xf8],rax
    2a8b:	00 
    2a8c:	31 c0                	xor    eax,eax
    2a8e:	48 8b 47 20          	mov    rax,QWORD PTR [rdi+0x20]
    2a92:	bf a8 03 00 00       	mov    edi,0x3a8
    2a97:	48 c7 44 24 08 00 00 	mov    QWORD PTR [rsp+0x8],0x0
    2a9e:	00 00 
    2aa0:	48 c7 44 24 18 ff ff 	mov    QWORD PTR [rsp+0x18],0xffffffffffffffff
    2aa7:	ff ff 
    2aa9:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
    2aae:	48 c7 44 24 48 ff ff 	mov    QWORD PTR [rsp+0x48],0xffffff
    2ab5:	ff 00 
    2ab7:	e8 04 f6 ff ff       	call   20c0 <malloc@plt>
    2abc:	48 89 c5             	mov    rbp,rax
    2abf:	48 85 c0             	test   rax,rax
    2ac2:	0f 84 ca 00 00 00    	je     2b92 <mlx_new_window+0x132>
    2ac8:	48 89 e0             	mov    rax,rsp
    2acb:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    2acf:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2ad2:	45 89 e9             	mov    r9d,r13d
    2ad5:	50                   	push   rax
    2ad6:	45 89 e0             	mov    r8d,r12d
    2ad9:	31 c9                	xor    ecx,ecx
    2adb:	31 d2                	xor    edx,edx
    2add:	68 0a 28 00 00       	push   0x280a
    2ae2:	ff 73 18             	push   QWORD PTR [rbx+0x18]
    2ae5:	6a 01                	push   0x1
    2ae7:	6a 00                	push   0x0
    2ae9:	6a 00                	push   0x0
    2aeb:	e8 f0 f5 ff ff       	call   20e0 <XCreateWindow@plt>
    2af0:	48 83 c4 30          	add    rsp,0x30
    2af4:	44 89 e9             	mov    ecx,r13d
    2af7:	44 89 e2             	mov    edx,r12d
    2afa:	48 89 45 00          	mov    QWORD PTR [rbp+0x0],rax
    2afe:	48 89 c6             	mov    rsi,rax
    2b01:	48 89 df             	mov    rdi,rbx
    2b04:	31 c0                	xor    eax,eax
    2b06:	e8 35 02 00 00       	call   2d40 <mlx_int_anti_resize_win>
    2b0b:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2b0f:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2b12:	4c 89 f2             	mov    rdx,r14
    2b15:	e8 26 f5 ff ff       	call   2040 <XStoreName@plt>
    2b1a:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2b1e:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2b21:	48 8d 53 70          	lea    rdx,[rbx+0x70]
    2b25:	b9 01 00 00 00       	mov    ecx,0x1
    2b2a:	e8 a1 f6 ff ff       	call   21d0 <XSetWMProtocols@plt>
    2b2f:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2b33:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2b36:	66 0f 76 c0          	pcmpeqd xmm0,xmm0
    2b3a:	48 8d 4c 24 70       	lea    rcx,[rsp+0x70]
    2b3f:	ba 07 00 00 00       	mov    edx,0x7
    2b44:	0f 11 44 24 78       	movups XMMWORD PTR [rsp+0x78],xmm0
    2b49:	c7 44 24 70 03 00 00 	mov    DWORD PTR [rsp+0x70],0x3
    2b50:	00 
    2b51:	e8 aa f6 ff ff       	call   2200 <XCreateGC@plt>
    2b56:	48 8d 55 48          	lea    rdx,[rbp+0x48]
    2b5a:	b9 6c 00 00 00       	mov    ecx,0x6c
    2b5f:	66 48 0f 6e c0       	movq   xmm0,rax
    2b64:	48 89 d7             	mov    rdi,rdx
    2b67:	31 c0                	xor    eax,eax
    2b69:	0f 16 43 30          	movhps xmm0,QWORD PTR [rbx+0x30]
    2b6d:	48 89 6b 30          	mov    QWORD PTR [rbx+0x30],rbp
    2b71:	0f 11 45 08          	movups XMMWORD PTR [rbp+0x8],xmm0
    2b75:	f3 48 ab             	rep stos QWORD PTR es:[rdi],rax
    2b78:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2b7b:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2b7f:	e8 6c f7 ff ff       	call   22f0 <XMapRaised@plt>
    2b84:	48 8b 75 00          	mov    rsi,QWORD PTR [rbp+0x0]
    2b88:	48 89 df             	mov    rdi,rbx
    2b8b:	31 c0                	xor    eax,eax
    2b8d:	e8 6e 02 00 00       	call   2e00 <mlx_int_wait_first_expose>
    2b92:	48 8b 84 24 f8 00 00 	mov    rax,QWORD PTR [rsp+0xf8]
    2b99:	00 
    2b9a:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    2ba1:	00 00 
    2ba3:	75 13                	jne    2bb8 <mlx_new_window+0x158>
    2ba5:	48 81 c4 00 01 00 00 	add    rsp,0x100
    2bac:	48 89 e8             	mov    rax,rbp
    2baf:	5b                   	pop    rbx
    2bb0:	5d                   	pop    rbp
    2bb1:	41 5c                	pop    r12
    2bb3:	41 5d                	pop    r13
    2bb5:	41 5e                	pop    r14
    2bb7:	c3                   	ret
    2bb8:	e8 83 f6 ff ff       	call   2240 <__stack_chk_fail@plt>
    2bbd:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000002bc0 <mlx_loop_end>:
    2bc0:	c7 87 80 00 00 00 01 	mov    DWORD PTR [rdi+0x80],0x1
    2bc7:	00 00 00 
    2bca:	b8 01 00 00 00       	mov    eax,0x1
    2bcf:	c3                   	ret

0000000000002bd0 <mlx_loop>:
    2bd0:	41 54                	push   r12
    2bd2:	55                   	push   rbp
    2bd3:	53                   	push   rbx
    2bd4:	48 89 fb             	mov    rbx,rdi
    2bd7:	48 81 ec e0 00 00 00 	sub    rsp,0xe0
    2bde:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2be5:	00 00 
    2be7:	48 89 84 24 d8 00 00 	mov    QWORD PTR [rsp+0xd8],rax
    2bee:	00 
    2bef:	31 c0                	xor    eax,eax
    2bf1:	48 8d 6c 24 10       	lea    rbp,[rsp+0x10]
    2bf6:	e8 c5 0a 00 00       	call   36c0 <mlx_int_set_win_event_mask>
    2bfb:	c7 43 50 00 00 00 00 	mov    DWORD PTR [rbx+0x50],0x0
    2c02:	4c 8d 25 b7 35 00 00 	lea    r12,[rip+0x35b7]        # 61c0 <mlx_int_param_event>
    2c09:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    2c10:	48 83 7b 30 00       	cmp    QWORD PTR [rbx+0x30],0x0
    2c15:	0f 84 f2 00 00 00    	je     2d0d <mlx_loop+0x13d>
    2c1b:	8b 83 80 00 00 00    	mov    eax,DWORD PTR [rbx+0x80]
    2c21:	85 c0                	test   eax,eax
    2c23:	0f 85 e4 00 00 00    	jne    2d0d <mlx_loop+0x13d>
    2c29:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2c2c:	85 c0                	test   eax,eax
    2c2e:	75 59                	jne    2c89 <mlx_loop+0xb9>
    2c30:	48 83 7b 38 00       	cmp    QWORD PTR [rbx+0x38],0x0
    2c35:	74 0c                	je     2c43 <mlx_loop+0x73>
    2c37:	e8 04 f7 ff ff       	call   2340 <XPending@plt>
    2c3c:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2c3f:	85 c0                	test   eax,eax
    2c41:	74 46                	je     2c89 <mlx_loop+0xb9>
    2c43:	48 89 ee             	mov    rsi,rbp
    2c46:	e8 65 f5 ff ff       	call   21b0 <XNextEvent@plt>
    2c4b:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
    2c4f:	48 85 d2             	test   rdx,rdx
    2c52:	74 28                	je     2c7c <mlx_loop+0xac>
    2c54:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
    2c59:	eb 0e                	jmp    2c69 <mlx_loop+0x99>
    2c5b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    2c60:	48 8b 52 10          	mov    rdx,QWORD PTR [rdx+0x10]
    2c64:	48 85 d2             	test   rdx,rdx
    2c67:	74 13                	je     2c7c <mlx_loop+0xac>
    2c69:	48 39 02             	cmp    QWORD PTR [rdx],rax
    2c6c:	75 f2                	jne    2c60 <mlx_loop+0x90>
    2c6e:	8b 44 24 10          	mov    eax,DWORD PTR [rsp+0x10]
    2c72:	83 f8 21             	cmp    eax,0x21
    2c75:	74 39                	je     2cb0 <mlx_loop+0xe0>
    2c77:	83 f8 23             	cmp    eax,0x23
    2c7a:	7e 3f                	jle    2cbb <mlx_loop+0xeb>
    2c7c:	8b 83 80 00 00 00    	mov    eax,DWORD PTR [rbx+0x80]
    2c82:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2c85:	85 c0                	test   eax,eax
    2c87:	74 a7                	je     2c30 <mlx_loop+0x60>
    2c89:	31 f6                	xor    esi,esi
    2c8b:	e8 a0 f5 ff ff       	call   2230 <XSync@plt>
    2c90:	48 8b 53 38          	mov    rdx,QWORD PTR [rbx+0x38]
    2c94:	48 85 d2             	test   rdx,rdx
    2c97:	0f 84 73 ff ff ff    	je     2c10 <mlx_loop+0x40>
    2c9d:	48 8b 7b 40          	mov    rdi,QWORD PTR [rbx+0x40]
    2ca1:	31 c0                	xor    eax,eax
    2ca3:	ff d2                	call   rdx
    2ca5:	e9 58 ff ff ff       	jmp    2c02 <mlx_loop+0x32>
    2caa:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2cb0:	48 8b 4b 78          	mov    rcx,QWORD PTR [rbx+0x78]
    2cb4:	48 39 4c 24 38       	cmp    QWORD PTR [rsp+0x38],rcx
    2cb9:	74 1d                	je     2cd8 <mlx_loop+0x108>
    2cbb:	48 63 c8             	movsxd rcx,eax
    2cbe:	48 8d 04 49          	lea    rax,[rcx+rcx*2]
    2cc2:	48 83 7c c2 50 00    	cmp    QWORD PTR [rdx+rax*8+0x50],0x0
    2cc8:	74 b2                	je     2c7c <mlx_loop+0xac>
    2cca:	48 89 ee             	mov    rsi,rbp
    2ccd:	48 89 df             	mov    rdi,rbx
    2cd0:	31 c0                	xor    eax,eax
    2cd2:	41 ff 14 cc          	call   QWORD PTR [r12+rcx*8]
    2cd6:	eb a4                	jmp    2c7c <mlx_loop+0xac>
    2cd8:	48 8b 73 70          	mov    rsi,QWORD PTR [rbx+0x70]
    2cdc:	48 39 74 24 48       	cmp    QWORD PTR [rsp+0x48],rsi
    2ce1:	75 d8                	jne    2cbb <mlx_loop+0xeb>
    2ce3:	48 8b 8a e8 01 00 00 	mov    rcx,QWORD PTR [rdx+0x1e8]
    2cea:	48 85 c9             	test   rcx,rcx
    2ced:	74 cc                	je     2cbb <mlx_loop+0xeb>
    2cef:	48 89 54 24 08       	mov    QWORD PTR [rsp+0x8],rdx
    2cf4:	48 8b ba f0 01 00 00 	mov    rdi,QWORD PTR [rdx+0x1f0]
    2cfb:	31 c0                	xor    eax,eax
    2cfd:	ff d1                	call   rcx
    2cff:	8b 44 24 10          	mov    eax,DWORD PTR [rsp+0x10]
    2d03:	48 8b 54 24 08       	mov    rdx,QWORD PTR [rsp+0x8]
    2d08:	e9 6a ff ff ff       	jmp    2c77 <mlx_loop+0xa7>
    2d0d:	48 8b 84 24 d8 00 00 	mov    rax,QWORD PTR [rsp+0xd8]
    2d14:	00 
    2d15:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    2d1c:	00 00 
    2d1e:	75 0e                	jne    2d2e <mlx_loop+0x15e>
    2d20:	48 81 c4 e0 00 00 00 	add    rsp,0xe0
    2d27:	31 c0                	xor    eax,eax
    2d29:	5b                   	pop    rbx
    2d2a:	5d                   	pop    rbp
    2d2b:	41 5c                	pop    r12
    2d2d:	c3                   	ret
    2d2e:	e8 0d f5 ff ff       	call   2240 <__stack_chk_fail@plt>
    2d33:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    2d3a:	00 00 00 
    2d3d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000002d40 <mlx_int_anti_resize_win>:
    2d40:	41 54                	push   r12
    2d42:	66 0f 6e ca          	movd   xmm1,edx
    2d46:	66 0f 6e c1          	movd   xmm0,ecx
    2d4a:	55                   	push   rbp
    2d4b:	66 0f 6f d1          	movdqa xmm2,xmm1
    2d4f:	48 89 fd             	mov    rbp,rdi
    2d52:	53                   	push   rbx
    2d53:	66 0f 62 d0          	punpckldq xmm2,xmm0
    2d57:	48 89 f3             	mov    rbx,rsi
    2d5a:	66 0f 6c d2          	punpcklqdq xmm2,xmm2
    2d5e:	48 81 ec 90 00 00 00 	sub    rsp,0x90
    2d65:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    2d68:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2d6f:	00 00 
    2d71:	48 89 84 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rax
    2d78:	00 
    2d79:	31 c0                	xor    eax,eax
    2d7b:	4c 8d 64 24 30       	lea    r12,[rsp+0x30]
    2d80:	89 54 24 1c          	mov    DWORD PTR [rsp+0x1c],edx
    2d84:	89 4c 24 18          	mov    DWORD PTR [rsp+0x18],ecx
    2d88:	4c 89 e2             	mov    rdx,r12
    2d8b:	48 8d 4c 24 28       	lea    rcx,[rsp+0x28]
    2d90:	0f 29 14 24          	movaps XMMWORD PTR [rsp],xmm2
    2d94:	e8 b7 f2 ff ff       	call   2050 <XGetWMNormalHints@plt>
    2d99:	66 0f 6f 14 24       	movdqa xmm2,XMMWORD PTR [rsp]
    2d9e:	4c 89 e2             	mov    rdx,r12
    2da1:	48 89 de             	mov    rsi,rbx
    2da4:	66 0f 6e 4c 24 1c    	movd   xmm1,DWORD PTR [rsp+0x1c]
    2daa:	66 0f 6e 44 24 18    	movd   xmm0,DWORD PTR [rsp+0x18]
    2db0:	48 c7 44 24 30 3c 00 	mov    QWORD PTR [rsp+0x30],0x3c
    2db7:	00 00 
    2db9:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    2dbd:	0f 29 54 24 40       	movaps XMMWORD PTR [rsp+0x40],xmm2
    2dc2:	66 0f 7e 4c 24 50    	movd   DWORD PTR [rsp+0x50],xmm1
    2dc8:	66 0f 7e 44 24 54    	movd   DWORD PTR [rsp+0x54],xmm0
    2dce:	e8 fd f2 ff ff       	call   20d0 <XSetWMNormalHints@plt>
    2dd3:	48 8b 84 24 88 00 00 	mov    rax,QWORD PTR [rsp+0x88]
    2dda:	00 
    2ddb:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    2de2:	00 00 
    2de4:	75 0e                	jne    2df4 <mlx_int_anti_resize_win+0xb4>
    2de6:	48 81 c4 90 00 00 00 	add    rsp,0x90
    2ded:	31 c0                	xor    eax,eax
    2def:	5b                   	pop    rbx
    2df0:	5d                   	pop    rbp
    2df1:	41 5c                	pop    r12
    2df3:	c3                   	ret
    2df4:	e8 47 f4 ff ff       	call   2240 <__stack_chk_fail@plt>
    2df9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000002e00 <mlx_int_wait_first_expose>:
    2e00:	55                   	push   rbp
    2e01:	ba 00 80 00 00       	mov    edx,0x8000
    2e06:	53                   	push   rbx
    2e07:	48 89 fb             	mov    rbx,rdi
    2e0a:	48 81 ec d8 00 00 00 	sub    rsp,0xd8
    2e11:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    2e14:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2e1b:	00 00 
    2e1d:	48 89 84 24 c8 00 00 	mov    QWORD PTR [rsp+0xc8],rax
    2e24:	00 
    2e25:	31 c0                	xor    eax,eax
    2e27:	48 89 e5             	mov    rbp,rsp
    2e2a:	48 89 e9             	mov    rcx,rbp
    2e2d:	e8 8e f3 ff ff       	call   21c0 <XWindowEvent@plt>
    2e32:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2e35:	48 89 ee             	mov    rsi,rbp
    2e38:	e8 b3 f3 ff ff       	call   21f0 <XPutBackEvent@plt>
    2e3d:	48 8b 84 24 c8 00 00 	mov    rax,QWORD PTR [rsp+0xc8]
    2e44:	00 
    2e45:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    2e4c:	00 00 
    2e4e:	75 0c                	jne    2e5c <mlx_int_wait_first_expose+0x5c>
    2e50:	48 81 c4 d8 00 00 00 	add    rsp,0xd8
    2e57:	31 c0                	xor    eax,eax
    2e59:	5b                   	pop    rbx
    2e5a:	5d                   	pop    rbp
    2e5b:	c3                   	ret
    2e5c:	e8 df f3 ff ff       	call   2240 <__stack_chk_fail@plt>
    2e61:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    2e68:	00 00 00 
    2e6b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000002e70 <mlx_int_get_visual>:
    2e70:	53                   	push   rbx
    2e71:	48 89 fb             	mov    rbx,rdi
    2e74:	48 83 ec 60          	sub    rsp,0x60
    2e78:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    2e7f:	00 00 
    2e81:	48 89 44 24 58       	mov    QWORD PTR [rsp+0x58],rax
    2e86:	31 c0                	xor    eax,eax
    2e88:	c7 47 28 00 00 00 00 	mov    DWORD PTR [rdi+0x28],0x0
    2e8f:	48 63 43 10          	movsxd rax,DWORD PTR [rbx+0x10]
    2e93:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    2e96:	48 c1 e0 07          	shl    rax,0x7
    2e9a:	48 03 87 e8 00 00 00 	add    rax,QWORD PTR [rdi+0xe8]
    2ea1:	48 8b 40 40          	mov    rax,QWORD PTR [rax+0x40]
    2ea5:	83 78 10 04          	cmp    DWORD PTR [rax+0x10],0x4
    2ea9:	48 89 43 18          	mov    QWORD PTR [rbx+0x18],rax
    2ead:	74 36                	je     2ee5 <mlx_int_get_visual+0x75>
    2eaf:	8b 43 14             	mov    eax,DWORD PTR [rbx+0x14]
    2eb2:	48 8d 4c 24 0c       	lea    rcx,[rsp+0xc]
    2eb7:	48 8d 54 24 10       	lea    rdx,[rsp+0x10]
    2ebc:	be 0c 00 00 00       	mov    esi,0xc
    2ec1:	c7 44 24 28 04 00 00 	mov    DWORD PTR [rsp+0x28],0x4
    2ec8:	00 
    2ec9:	89 44 24 24          	mov    DWORD PTR [rsp+0x24],eax
    2ecd:	e8 ce f3 ff ff       	call   22a0 <XGetVisualInfo@plt>
    2ed2:	48 85 c0             	test   rax,rax
    2ed5:	74 26                	je     2efd <mlx_int_get_visual+0x8d>
    2ed7:	48 8b 00             	mov    rax,QWORD PTR [rax]
    2eda:	c7 43 28 01 00 00 00 	mov    DWORD PTR [rbx+0x28],0x1
    2ee1:	48 89 43 18          	mov    QWORD PTR [rbx+0x18],rax
    2ee5:	31 c0                	xor    eax,eax
    2ee7:	48 8b 54 24 58       	mov    rdx,QWORD PTR [rsp+0x58]
    2eec:	64 48 2b 14 25 28 00 	sub    rdx,QWORD PTR fs:0x28
    2ef3:	00 00 
    2ef5:	75 0d                	jne    2f04 <mlx_int_get_visual+0x94>
    2ef7:	48 83 c4 60          	add    rsp,0x60
    2efb:	5b                   	pop    rbx
    2efc:	c3                   	ret
    2efd:	b8 ff ff ff ff       	mov    eax,0xffffffff
    2f02:	eb e3                	jmp    2ee7 <mlx_int_get_visual+0x77>
    2f04:	e8 37 f3 ff ff       	call   2240 <__stack_chk_fail@plt>
    2f09:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000002f10 <shm_att_pb>:
    2f10:	8b 46 20             	mov    eax,DWORD PTR [rsi+0x20]
    2f13:	25 00 ff ff 00       	and    eax,0xffff00
    2f18:	3d 00 92 01 00       	cmp    eax,0x19200
    2f1d:	74 11                	je     2f30 <shm_att_pb+0x20>
    2f1f:	c7 05 bb 33 00 00 01 	mov    DWORD PTR [rip+0x33bb],0x1        # 62e4 <mlx_X_error>
    2f26:	00 00 00 
    2f29:	c3                   	ret
    2f2a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    2f30:	48 83 ec 08          	sub    rsp,0x8
    2f34:	ba 38 00 00 00       	mov    edx,0x38
    2f39:	bf 02 00 00 00       	mov    edi,0x2
    2f3e:	48 8d 35 db 11 00 00 	lea    rsi,[rip+0x11db]        # 4120 <_IO_stdin_used+0x120>
    2f45:	e8 c6 f3 ff ff       	call   2310 <write@plt>
    2f4a:	c7 05 90 33 00 00 01 	mov    DWORD PTR [rip+0x3390],0x1        # 62e4 <mlx_X_error>
    2f51:	00 00 00 
    2f54:	48 83 c4 08          	add    rsp,0x8
    2f58:	c3                   	ret
    2f59:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000000002f60 <mlx_int_new_xshm_image>:
    2f60:	41 57                	push   r15
    2f62:	41 56                	push   r14
    2f64:	41 55                	push   r13
    2f66:	41 89 cd             	mov    r13d,ecx
    2f69:	41 54                	push   r12
    2f6b:	41 89 d4             	mov    r12d,edx
    2f6e:	55                   	push   rbp
    2f6f:	89 f5                	mov    ebp,esi
    2f71:	be 01 00 00 00       	mov    esi,0x1
    2f76:	53                   	push   rbx
    2f77:	48 89 fb             	mov    rbx,rdi
    2f7a:	bf 58 00 00 00       	mov    edi,0x58
    2f7f:	48 83 ec 18          	sub    rsp,0x18
    2f83:	e8 e8 f2 ff ff       	call   2270 <calloc@plt>
    2f88:	48 85 c0             	test   rax,rax
    2f8b:	0f 84 7e 01 00 00    	je     310f <mlx_int_new_xshm_image+0x1af>
    2f91:	49 89 c6             	mov    r14,rax
    2f94:	48 8d 40 38          	lea    rax,[rax+0x38]
    2f98:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    2f9b:	8b 53 14             	mov    edx,DWORD PTR [rbx+0x14]
    2f9e:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
    2fa3:	48 8b 73 18          	mov    rsi,QWORD PTR [rbx+0x18]
    2fa7:	45 31 c0             	xor    r8d,r8d
    2faa:	49 89 c1             	mov    r9,rax
    2fad:	41 54                	push   r12
    2faf:	44 89 e9             	mov    ecx,r13d
    2fb2:	55                   	push   rbp
    2fb3:	e8 c8 f1 ff ff       	call   2180 <XShmCreateImage@plt>
    2fb8:	49 89 06             	mov    QWORD PTR [r14],rax
    2fbb:	5f                   	pop    rdi
    2fbc:	41 58                	pop    r8
    2fbe:	48 85 c0             	test   rax,rax
    2fc1:	0f 84 99 01 00 00    	je     3160 <mlx_int_new_xshm_image+0x200>
    2fc7:	8d 75 20             	lea    esi,[rbp+0x20]
    2fca:	66 0f 6e 40 2c       	movd   xmm0,DWORD PTR [rax+0x2c]
    2fcf:	66 0f 6e 50 30       	movd   xmm2,DWORD PTR [rax+0x30]
    2fd4:	31 ff                	xor    edi,edi
    2fd6:	41 0f af f4          	imul   esi,r12d
    2fda:	66 41 0f 6e dc       	movd   xmm3,r12d
    2fdf:	66 0f 6e cd          	movd   xmm1,ebp
    2fe3:	45 89 6e 2c          	mov    DWORD PTR [r14+0x2c],r13d
    2fe7:	66 0f 62 c2          	punpckldq xmm0,xmm2
    2feb:	66 0f 62 cb          	punpckldq xmm1,xmm3
    2fef:	ba ff 03 00 00       	mov    edx,0x3ff
    2ff4:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
    2ff8:	c1 e6 02             	shl    esi,0x2
    2ffb:	41 0f 11 46 18       	movups XMMWORD PTR [r14+0x18],xmm0
    3000:	48 63 f6             	movsxd rsi,esi
    3003:	e8 78 f2 ff ff       	call   2280 <shmget@plt>
    3008:	41 89 46 40          	mov    DWORD PTR [r14+0x40],eax
    300c:	89 c7                	mov    edi,eax
    300e:	83 f8 ff             	cmp    eax,0xffffffff
    3011:	0f 84 e7 00 00 00    	je     30fe <mlx_int_new_xshm_image+0x19e>
    3017:	4d 8b 3e             	mov    r15,QWORD PTR [r14]
    301a:	31 d2                	xor    edx,edx
    301c:	31 f6                	xor    esi,esi
    301e:	e8 2d f3 ff ff       	call   2350 <shmat@plt>
    3023:	49 89 47 10          	mov    QWORD PTR [r15+0x10],rax
    3027:	49 89 46 48          	mov    QWORD PTR [r14+0x48],rax
    302b:	49 89 46 30          	mov    QWORD PTR [r14+0x30],rax
    302f:	48 83 f8 ff          	cmp    rax,0xffffffffffffffff
    3033:	0f 84 b8 00 00 00    	je     30f1 <mlx_int_new_xshm_image+0x191>
    3039:	41 c7 46 50 00 00 00 	mov    DWORD PTR [r14+0x50],0x0
    3040:	00 
    3041:	48 8d 3d c8 fe ff ff 	lea    rdi,[rip+0xfffffffffffffec8]        # 2f10 <shm_att_pb>
    3048:	c7 05 92 32 00 00 00 	mov    DWORD PTR [rip+0x3292],0x0        # 62e4 <mlx_X_error>
    304f:	00 00 00 
    3052:	e8 69 f2 ff ff       	call   22c0 <XSetErrorHandler@plt>
    3057:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    305a:	48 8b 74 24 08       	mov    rsi,QWORD PTR [rsp+0x8]
    305f:	49 89 c7             	mov    r15,rax
    3062:	e8 f9 f1 ff ff       	call   2260 <XShmAttach@plt>
    3067:	85 c0                	test   eax,eax
    3069:	74 75                	je     30e0 <mlx_int_new_xshm_image+0x180>
    306b:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    306e:	31 f6                	xor    esi,esi
    3070:	e8 bb f1 ff ff       	call   2230 <XSync@plt>
    3075:	8b 35 69 32 00 00    	mov    esi,DWORD PTR [rip+0x3269]        # 62e4 <mlx_X_error>
    307b:	85 f6                	test   esi,esi
    307d:	75 61                	jne    30e0 <mlx_int_new_xshm_image+0x180>
    307f:	4c 89 ff             	mov    rdi,r15
    3082:	e8 39 f2 ff ff       	call   22c0 <XSetErrorHandler@plt>
    3087:	41 8b 7e 40          	mov    edi,DWORD PTR [r14+0x40]
    308b:	31 d2                	xor    edx,edx
    308d:	31 f6                	xor    esi,esi
    308f:	e8 3c f2 ff ff       	call   22d0 <shmctl@plt>
    3094:	44 39 6b 4c          	cmp    DWORD PTR [rbx+0x4c],r13d
    3098:	0f 84 8a 00 00 00    	je     3128 <mlx_int_new_xshm_image+0x1c8>
    309e:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    30a2:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    30a5:	89 ea                	mov    edx,ebp
    30a7:	44 89 e1             	mov    ecx,r12d
    30aa:	44 8b 43 14          	mov    r8d,DWORD PTR [rbx+0x14]
    30ae:	e8 2d f2 ff ff       	call   22e0 <XCreatePixmap@plt>
    30b3:	ba 02 00 00 00       	mov    edx,0x2
    30b8:	49 89 46 08          	mov    QWORD PTR [r14+0x8],rax
    30bc:	8b 43 50             	mov    eax,DWORD PTR [rbx+0x50]
    30bf:	41 89 56 28          	mov    DWORD PTR [r14+0x28],edx
    30c3:	85 c0                	test   eax,eax
    30c5:	75 51                	jne    3118 <mlx_int_new_xshm_image+0x1b8>
    30c7:	48 83 c4 18          	add    rsp,0x18
    30cb:	4c 89 f0             	mov    rax,r14
    30ce:	5b                   	pop    rbx
    30cf:	5d                   	pop    rbp
    30d0:	41 5c                	pop    r12
    30d2:	41 5d                	pop    r13
    30d4:	41 5e                	pop    r14
    30d6:	41 5f                	pop    r15
    30d8:	c3                   	ret
    30d9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    30e0:	4c 89 ff             	mov    rdi,r15
    30e3:	e8 d8 f1 ff ff       	call   22c0 <XSetErrorHandler@plt>
    30e8:	49 8b 7e 30          	mov    rdi,QWORD PTR [r14+0x30]
    30ec:	e8 3f ef ff ff       	call   2030 <shmdt@plt>
    30f1:	41 8b 7e 40          	mov    edi,DWORD PTR [r14+0x40]
    30f5:	31 d2                	xor    edx,edx
    30f7:	31 f6                	xor    esi,esi
    30f9:	e8 d2 f1 ff ff       	call   22d0 <shmctl@plt>
    30fe:	49 8b 06             	mov    rax,QWORD PTR [r14]
    3101:	48 89 c7             	mov    rdi,rax
    3104:	ff 50 60             	call   QWORD PTR [rax+0x60]
    3107:	4c 89 f7             	mov    rdi,r14
    310a:	e8 21 f0 ff ff       	call   2130 <free@plt>
    310f:	45 31 f6             	xor    r14d,r14d
    3112:	eb b3                	jmp    30c7 <mlx_int_new_xshm_image+0x167>
    3114:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    3118:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    311b:	e8 00 f1 ff ff       	call   2220 <XFlush@plt>
    3120:	eb a5                	jmp    30c7 <mlx_int_new_xshm_image+0x167>
    3122:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3128:	8b 43 14             	mov    eax,DWORD PTR [rbx+0x14]
    312b:	48 83 ec 08          	sub    rsp,0x8
    312f:	49 8b 56 48          	mov    rdx,QWORD PTR [r14+0x48]
    3133:	45 89 e1             	mov    r9d,r12d
    3136:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    313a:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
    313d:	41 89 e8             	mov    r8d,ebp
    3140:	50                   	push   rax
    3141:	48 8b 4c 24 18       	mov    rcx,QWORD PTR [rsp+0x18]
    3146:	e8 55 ef ff ff       	call   20a0 <XShmCreatePixmap@plt>
    314b:	5a                   	pop    rdx
    314c:	ba 03 00 00 00       	mov    edx,0x3
    3151:	59                   	pop    rcx
    3152:	e9 61 ff ff ff       	jmp    30b8 <mlx_int_new_xshm_image+0x158>
    3157:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    315e:	00 00 
    3160:	4c 89 f7             	mov    rdi,r14
    3163:	e8 c8 ef ff ff       	call   2130 <free@plt>
    3168:	eb a5                	jmp    310f <mlx_int_new_xshm_image+0x1af>
    316a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000003170 <mlx_int_new_image>:
    3170:	41 56                	push   r14
    3172:	41 89 ce             	mov    r14d,ecx
    3175:	41 55                	push   r13
    3177:	41 89 d5             	mov    r13d,edx
    317a:	41 54                	push   r12
    317c:	41 89 f4             	mov    r12d,esi
    317f:	55                   	push   rbp
    3180:	48 89 fd             	mov    rbp,rdi
    3183:	bf 58 00 00 00       	mov    edi,0x58
    3188:	53                   	push   rbx
    3189:	e8 32 ef ff ff       	call   20c0 <malloc@plt>
    318e:	48 85 c0             	test   rax,rax
    3191:	0f 84 f2 00 00 00    	je     3289 <mlx_int_new_image+0x119>
    3197:	41 8d 7c 24 20       	lea    edi,[r12+0x20]
    319c:	be 01 00 00 00       	mov    esi,0x1
    31a1:	48 89 c3             	mov    rbx,rax
    31a4:	41 0f af fd          	imul   edi,r13d
    31a8:	c1 e7 02             	shl    edi,0x2
    31ab:	48 63 ff             	movsxd rdi,edi
    31ae:	e8 bd f0 ff ff       	call   2270 <calloc@plt>
    31b3:	48 89 43 30          	mov    QWORD PTR [rbx+0x30],rax
    31b7:	49 89 c1             	mov    r9,rax
    31ba:	48 85 c0             	test   rax,rax
    31bd:	0f 84 ca 00 00 00    	je     328d <mlx_int_new_image+0x11d>
    31c3:	8b 55 14             	mov    edx,DWORD PTR [rbp+0x14]
    31c6:	48 8b 75 18          	mov    rsi,QWORD PTR [rbp+0x18]
    31ca:	45 31 c0             	xor    r8d,r8d
    31cd:	44 89 f1             	mov    ecx,r14d
    31d0:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    31d4:	6a 00                	push   0x0
    31d6:	6a 20                	push   0x20
    31d8:	41 55                	push   r13
    31da:	41 54                	push   r12
    31dc:	e8 af ee ff ff       	call   2090 <XCreateImage@plt>
    31e1:	48 83 c4 20          	add    rsp,0x20
    31e5:	48 89 03             	mov    QWORD PTR [rbx],rax
    31e8:	48 85 c0             	test   rax,rax
    31eb:	0f 84 87 00 00 00    	je     3278 <mlx_int_new_image+0x108>
    31f1:	66 0f 6e 40 2c       	movd   xmm0,DWORD PTR [rax+0x2c]
    31f6:	66 0f 6e 58 30       	movd   xmm3,DWORD PTR [rax+0x30]
    31fb:	44 89 e9             	mov    ecx,r13d
    31fe:	44 89 e2             	mov    edx,r12d
    3201:	66 41 0f 6e d5       	movd   xmm2,r13d
    3206:	66 41 0f 6e cc       	movd   xmm1,r12d
    320b:	48 8b 75 08          	mov    rsi,QWORD PTR [rbp+0x8]
    320f:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3213:	66 0f 62 ca          	punpckldq xmm1,xmm2
    3217:	66 0f 62 c3          	punpckldq xmm0,xmm3
    321b:	48 c7 43 10 00 00 00 	mov    QWORD PTR [rbx+0x10],0x0
    3222:	00 
    3223:	44 8b 45 14          	mov    r8d,DWORD PTR [rbp+0x14]
    3227:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
    322b:	0f 11 43 18          	movups XMMWORD PTR [rbx+0x18],xmm0
    322f:	e8 ac f0 ff ff       	call   22e0 <XCreatePixmap@plt>
    3234:	44 89 73 2c          	mov    DWORD PTR [rbx+0x2c],r14d
    3238:	48 89 43 08          	mov    QWORD PTR [rbx+0x8],rax
    323c:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    323f:	c7 43 28 01 00 00 00 	mov    DWORD PTR [rbx+0x28],0x1
    3246:	85 c0                	test   eax,eax
    3248:	75 16                	jne    3260 <mlx_int_new_image+0xf0>
    324a:	48 89 d8             	mov    rax,rbx
    324d:	5b                   	pop    rbx
    324e:	5d                   	pop    rbp
    324f:	41 5c                	pop    r12
    3251:	41 5d                	pop    r13
    3253:	41 5e                	pop    r14
    3255:	c3                   	ret
    3256:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    325d:	00 00 00 
    3260:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3264:	e8 b7 ef ff ff       	call   2220 <XFlush@plt>
    3269:	48 89 d8             	mov    rax,rbx
    326c:	5b                   	pop    rbx
    326d:	5d                   	pop    rbp
    326e:	41 5c                	pop    r12
    3270:	41 5d                	pop    r13
    3272:	41 5e                	pop    r14
    3274:	c3                   	ret
    3275:	0f 1f 00             	nop    DWORD PTR [rax]
    3278:	48 8b 7b 30          	mov    rdi,QWORD PTR [rbx+0x30]
    327c:	e8 af ee ff ff       	call   2130 <free@plt>
    3281:	48 89 df             	mov    rdi,rbx
    3284:	e8 a7 ee ff ff       	call   2130 <free@plt>
    3289:	31 db                	xor    ebx,ebx
    328b:	eb bd                	jmp    324a <mlx_int_new_image+0xda>
    328d:	48 89 df             	mov    rdi,rbx
    3290:	31 db                	xor    ebx,ebx
    3292:	e8 99 ee ff ff       	call   2130 <free@plt>
    3297:	eb b1                	jmp    324a <mlx_int_new_image+0xda>
    3299:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

00000000000032a0 <mlx_new_image>:
    32a0:	41 54                	push   r12
    32a2:	41 89 d4             	mov    r12d,edx
    32a5:	55                   	push   rbp
    32a6:	89 f5                	mov    ebp,esi
    32a8:	53                   	push   rbx
    32a9:	8b 47 48             	mov    eax,DWORD PTR [rdi+0x48]
    32ac:	48 89 fb             	mov    rbx,rdi
    32af:	85 c0                	test   eax,eax
    32b1:	74 1d                	je     32d0 <mlx_new_image+0x30>
    32b3:	b9 02 00 00 00       	mov    ecx,0x2
    32b8:	e8 a3 fc ff ff       	call   2f60 <mlx_int_new_xshm_image>
    32bd:	48 85 c0             	test   rax,rax
    32c0:	74 0e                	je     32d0 <mlx_new_image+0x30>
    32c2:	5b                   	pop    rbx
    32c3:	5d                   	pop    rbp
    32c4:	41 5c                	pop    r12
    32c6:	c3                   	ret
    32c7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    32ce:	00 00 
    32d0:	44 89 e2             	mov    edx,r12d
    32d3:	89 ee                	mov    esi,ebp
    32d5:	48 89 df             	mov    rdi,rbx
    32d8:	b9 02 00 00 00       	mov    ecx,0x2
    32dd:	5b                   	pop    rbx
    32de:	5d                   	pop    rbp
    32df:	41 5c                	pop    r12
    32e1:	e9 8a fe ff ff       	jmp    3170 <mlx_int_new_image>
    32e6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    32ed:	00 00 00 

00000000000032f0 <mlx_new_image2>:
    32f0:	41 54                	push   r12
    32f2:	41 89 d4             	mov    r12d,edx
    32f5:	55                   	push   rbp
    32f6:	89 f5                	mov    ebp,esi
    32f8:	53                   	push   rbx
    32f9:	8b 47 48             	mov    eax,DWORD PTR [rdi+0x48]
    32fc:	48 89 fb             	mov    rbx,rdi
    32ff:	85 c0                	test   eax,eax
    3301:	74 1d                	je     3320 <mlx_new_image2+0x30>
    3303:	b9 01 00 00 00       	mov    ecx,0x1
    3308:	e8 53 fc ff ff       	call   2f60 <mlx_int_new_xshm_image>
    330d:	48 85 c0             	test   rax,rax
    3310:	74 0e                	je     3320 <mlx_new_image2+0x30>
    3312:	5b                   	pop    rbx
    3313:	5d                   	pop    rbp
    3314:	41 5c                	pop    r12
    3316:	c3                   	ret
    3317:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    331e:	00 00 
    3320:	44 89 e2             	mov    edx,r12d
    3323:	89 ee                	mov    esi,ebp
    3325:	48 89 df             	mov    rdi,rbx
    3328:	b9 01 00 00 00       	mov    ecx,0x1
    332d:	5b                   	pop    rbx
    332e:	5d                   	pop    rbp
    332f:	41 5c                	pop    r12
    3331:	e9 3a fe ff ff       	jmp    3170 <mlx_int_new_image>
    3336:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    333d:	00 00 00 

0000000000003340 <mlx_put_image_to_window>:
    3340:	41 57                	push   r15
    3342:	41 56                	push   r14
    3344:	45 89 c6             	mov    r14d,r8d
    3347:	41 55                	push   r13
    3349:	41 89 cd             	mov    r13d,ecx
    334c:	41 54                	push   r12
    334e:	49 89 f4             	mov    r12,rsi
    3351:	55                   	push   rbp
    3352:	48 89 fd             	mov    rbp,rdi
    3355:	53                   	push   rbx
    3356:	48 89 d3             	mov    rbx,rdx
    3359:	48 83 ec 18          	sub    rsp,0x18
    335d:	4c 8b 7a 10          	mov    r15,QWORD PTR [rdx+0x10]
    3361:	4c 8b 56 08          	mov    r10,QWORD PTR [rsi+0x8]
    3365:	4d 85 ff             	test   r15,r15
    3368:	74 14                	je     337e <mlx_put_image_to_window+0x3e>
    336a:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    336d:	44 89 c1             	mov    ecx,r8d
    3370:	44 89 ea             	mov    edx,r13d
    3373:	4c 89 fe             	mov    rsi,r15
    3376:	e8 a5 ef ff ff       	call   2320 <XSetClipOrigin@plt>
    337b:	4d 89 fa             	mov    r10,r15
    337e:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    3381:	83 f8 02             	cmp    eax,0x2
    3384:	0f 84 a6 00 00 00    	je     3430 <mlx_put_image_to_window+0xf0>
    338a:	83 f8 01             	cmp    eax,0x1
    338d:	74 61                	je     33f0 <mlx_put_image_to_window+0xb0>
    338f:	49 8b 14 24          	mov    rdx,QWORD PTR [r12]
    3393:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    3397:	45 31 c9             	xor    r9d,r9d
    339a:	45 31 c0             	xor    r8d,r8d
    339d:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    33a1:	41 56                	push   r14
    33a3:	4c 89 d1             	mov    rcx,r10
    33a6:	41 55                	push   r13
    33a8:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    33ab:	50                   	push   rax
    33ac:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    33af:	50                   	push   rax
    33b0:	e8 8b ed ff ff       	call   2140 <XCopyArea@plt>
    33b5:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    33b8:	48 83 c4 20          	add    rsp,0x20
    33bc:	85 c0                	test   eax,eax
    33be:	75 10                	jne    33d0 <mlx_put_image_to_window+0x90>
    33c0:	48 83 c4 18          	add    rsp,0x18
    33c4:	5b                   	pop    rbx
    33c5:	5d                   	pop    rbp
    33c6:	41 5c                	pop    r12
    33c8:	41 5d                	pop    r13
    33ca:	41 5e                	pop    r14
    33cc:	41 5f                	pop    r15
    33ce:	c3                   	ret
    33cf:	90                   	nop
    33d0:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    33d4:	48 83 c4 18          	add    rsp,0x18
    33d8:	5b                   	pop    rbx
    33d9:	5d                   	pop    rbp
    33da:	41 5c                	pop    r12
    33dc:	41 5d                	pop    r13
    33de:	41 5e                	pop    r14
    33e0:	41 5f                	pop    r15
    33e2:	e9 39 ee ff ff       	jmp    2220 <XFlush@plt>
    33e7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    33ee:	00 00 
    33f0:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    33f3:	4c 89 54 24 08       	mov    QWORD PTR [rsp+0x8],r10
    33f8:	45 31 c9             	xor    r9d,r9d
    33fb:	45 31 c0             	xor    r8d,r8d
    33fe:	48 8b 0b             	mov    rcx,QWORD PTR [rbx]
    3401:	49 8b 54 24 08       	mov    rdx,QWORD PTR [r12+0x8]
    3406:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    340a:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    340e:	50                   	push   rax
    340f:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    3412:	50                   	push   rax
    3413:	6a 00                	push   0x0
    3415:	6a 00                	push   0x0
    3417:	e8 34 ee ff ff       	call   2250 <XPutImage@plt>
    341c:	48 83 c4 20          	add    rsp,0x20
    3420:	4c 8b 54 24 08       	mov    r10,QWORD PTR [rsp+0x8]
    3425:	e9 65 ff ff ff       	jmp    338f <mlx_put_image_to_window+0x4f>
    342a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3430:	4c 89 54 24 08       	mov    QWORD PTR [rsp+0x8],r10
    3435:	48 83 ec 08          	sub    rsp,0x8
    3439:	48 8b 0b             	mov    rcx,QWORD PTR [rbx]
    343c:	45 31 c9             	xor    r9d,r9d
    343f:	49 8b 54 24 08       	mov    rdx,QWORD PTR [r12+0x8]
    3444:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    3448:	45 31 c0             	xor    r8d,r8d
    344b:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    344f:	6a 00                	push   0x0
    3451:	8b 43 24             	mov    eax,DWORD PTR [rbx+0x24]
    3454:	50                   	push   rax
    3455:	8b 43 20             	mov    eax,DWORD PTR [rbx+0x20]
    3458:	50                   	push   rax
    3459:	6a 00                	push   0x0
    345b:	6a 00                	push   0x0
    345d:	e8 4e ee ff ff       	call   22b0 <XShmPutImage@plt>
    3462:	48 83 c4 30          	add    rsp,0x30
    3466:	8b 43 28             	mov    eax,DWORD PTR [rbx+0x28]
    3469:	4c 8b 54 24 08       	mov    r10,QWORD PTR [rsp+0x8]
    346e:	e9 17 ff ff ff       	jmp    338a <mlx_put_image_to_window+0x4a>
    3473:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    347a:	00 00 00 
    347d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000003480 <mlx_destroy_window>:
    3480:	55                   	push   rbp
    3481:	48 89 fd             	mov    rbp,rdi
    3484:	53                   	push   rbx
    3485:	48 89 f3             	mov    rbx,rsi
    3488:	48 81 ec b8 03 00 00 	sub    rsp,0x3b8
    348f:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    3496:	00 00 
    3498:	48 89 84 24 a8 03 00 	mov    QWORD PTR [rsp+0x3a8],rax
    349f:	00 
    34a0:	48 8b 47 30          	mov    rax,QWORD PTR [rdi+0x30]
    34a4:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
    34a9:	48 85 c0             	test   rax,rax
    34ac:	74 30                	je     34de <mlx_destroy_window+0x5e>
    34ae:	48 89 e1             	mov    rcx,rsp
    34b1:	eb 14                	jmp    34c7 <mlx_destroy_window+0x47>
    34b3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
    34b8:	48 8b 50 10          	mov    rdx,QWORD PTR [rax+0x10]
    34bc:	48 85 d2             	test   rdx,rdx
    34bf:	74 18                	je     34d9 <mlx_destroy_window+0x59>
    34c1:	48 89 c1             	mov    rcx,rax
    34c4:	48 89 d0             	mov    rax,rdx
    34c7:	48 39 c3             	cmp    rbx,rax
    34ca:	75 ec                	jne    34b8 <mlx_destroy_window+0x38>
    34cc:	48 8b 53 10          	mov    rdx,QWORD PTR [rbx+0x10]
    34d0:	48 89 51 10          	mov    QWORD PTR [rcx+0x10],rdx
    34d4:	48 85 d2             	test   rdx,rdx
    34d7:	75 eb                	jne    34c4 <mlx_destroy_window+0x44>
    34d9:	48 8b 44 24 10       	mov    rax,QWORD PTR [rsp+0x10]
    34de:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
    34e1:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    34e5:	48 89 45 30          	mov    QWORD PTR [rbp+0x30],rax
    34e9:	e8 72 ec ff ff       	call   2160 <XDestroyWindow@plt>
    34ee:	48 8b 73 08          	mov    rsi,QWORD PTR [rbx+0x8]
    34f2:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    34f6:	e8 95 ec ff ff       	call   2190 <XFreeGC@plt>
    34fb:	48 89 df             	mov    rdi,rbx
    34fe:	e8 2d ec ff ff       	call   2130 <free@plt>
    3503:	8b 45 50             	mov    eax,DWORD PTR [rbp+0x50]
    3506:	85 c0                	test   eax,eax
    3508:	75 26                	jne    3530 <mlx_destroy_window+0xb0>
    350a:	48 8b 84 24 a8 03 00 	mov    rax,QWORD PTR [rsp+0x3a8]
    3511:	00 
    3512:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3519:	00 00 
    351b:	75 38                	jne    3555 <mlx_destroy_window+0xd5>
    351d:	48 81 c4 b8 03 00 00 	add    rsp,0x3b8
    3524:	31 c0                	xor    eax,eax
    3526:	5b                   	pop    rbx
    3527:	5d                   	pop    rbp
    3528:	c3                   	ret
    3529:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    3530:	48 8b 84 24 a8 03 00 	mov    rax,QWORD PTR [rsp+0x3a8]
    3537:	00 
    3538:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    353f:	00 00 
    3541:	75 12                	jne    3555 <mlx_destroy_window+0xd5>
    3543:	48 8b 7d 00          	mov    rdi,QWORD PTR [rbp+0x0]
    3547:	48 81 c4 b8 03 00 00 	add    rsp,0x3b8
    354e:	5b                   	pop    rbx
    354f:	5d                   	pop    rbp
    3550:	e9 cb ec ff ff       	jmp    2220 <XFlush@plt>
    3555:	e8 e6 ec ff ff       	call   2240 <__stack_chk_fail@plt>
    355a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000003560 <mlx_int_param_undef>:
    3560:	c3                   	ret
    3561:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    3568:	00 00 00 00 
    356c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000003570 <mlx_int_param_ButtonPress>:
    3570:	44 8b 4e 44          	mov    r9d,DWORD PTR [rsi+0x44]
    3574:	8b 46 40             	mov    eax,DWORD PTR [rsi+0x40]
    3577:	48 8b 8a b8 00 00 00 	mov    rcx,QWORD PTR [rdx+0xb8]
    357e:	8b 7e 54             	mov    edi,DWORD PTR [rsi+0x54]
    3581:	4c 8b 82 b0 00 00 00 	mov    r8,QWORD PTR [rdx+0xb0]
    3588:	89 c6                	mov    esi,eax
    358a:	44 89 ca             	mov    edx,r9d
    358d:	31 c0                	xor    eax,eax
    358f:	41 ff e0             	jmp    r8
    3592:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    3599:	00 00 00 00 
    359d:	0f 1f 00             	nop    DWORD PTR [rax]

00000000000035a0 <mlx_int_param_ButtonRelease>:
    35a0:	44 8b 4e 44          	mov    r9d,DWORD PTR [rsi+0x44]
    35a4:	8b 46 40             	mov    eax,DWORD PTR [rsi+0x40]
    35a7:	48 8b 8a d0 00 00 00 	mov    rcx,QWORD PTR [rdx+0xd0]
    35ae:	8b 7e 54             	mov    edi,DWORD PTR [rsi+0x54]
    35b1:	4c 8b 82 c8 00 00 00 	mov    r8,QWORD PTR [rdx+0xc8]
    35b8:	89 c6                	mov    esi,eax
    35ba:	44 89 ca             	mov    edx,r9d
    35bd:	31 c0                	xor    eax,eax
    35bf:	41 ff e0             	jmp    r8
    35c2:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    35c9:	00 00 00 00 
    35cd:	0f 1f 00             	nop    DWORD PTR [rax]

00000000000035d0 <mlx_int_param_MotionNotify>:
    35d0:	8b 46 44             	mov    eax,DWORD PTR [rsi+0x44]
    35d3:	4c 8b 82 e8 00 00 00 	mov    r8,QWORD PTR [rdx+0xe8]
    35da:	8b 7e 40             	mov    edi,DWORD PTR [rsi+0x40]
    35dd:	48 8b 8a e0 00 00 00 	mov    rcx,QWORD PTR [rdx+0xe0]
    35e4:	89 c6                	mov    esi,eax
    35e6:	4c 89 c2             	mov    rdx,r8
    35e9:	31 c0                	xor    eax,eax
    35eb:	ff e1                	jmp    rcx
    35ed:	0f 1f 00             	nop    DWORD PTR [rax]

00000000000035f0 <mlx_int_param_generic>:
    35f0:	48 63 06             	movsxd rax,DWORD PTR [rsi]
    35f3:	48 8d 04 40          	lea    rax,[rax+rax*2]
    35f7:	48 8d 04 c2          	lea    rax,[rdx+rax*8]
    35fb:	48 8b 78 58          	mov    rdi,QWORD PTR [rax+0x58]
    35ff:	48 8b 50 50          	mov    rdx,QWORD PTR [rax+0x50]
    3603:	31 c0                	xor    eax,eax
    3605:	ff e2                	jmp    rdx
    3607:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    360e:	00 00 

0000000000003610 <mlx_int_param_KeyPress>:
    3610:	55                   	push   rbp
    3611:	31 c9                	xor    ecx,ecx
    3613:	53                   	push   rbx
    3614:	48 83 ec 08          	sub    rsp,0x8
    3618:	0f b6 76 54          	movzx  esi,BYTE PTR [rsi+0x54]
    361c:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    361f:	48 8b 9a 80 00 00 00 	mov    rbx,QWORD PTR [rdx+0x80]
    3626:	48 8b aa 88 00 00 00 	mov    rbp,QWORD PTR [rdx+0x88]
    362d:	31 d2                	xor    edx,edx
    362f:	e8 bc ea ff ff       	call   20f0 <XkbKeycodeToKeysym@plt>
    3634:	48 83 c4 08          	add    rsp,0x8
    3638:	48 89 c7             	mov    rdi,rax
    363b:	48 89 ee             	mov    rsi,rbp
    363e:	48 89 d9             	mov    rcx,rbx
    3641:	31 c0                	xor    eax,eax
    3643:	5b                   	pop    rbx
    3644:	5d                   	pop    rbp
    3645:	ff e1                	jmp    rcx
    3647:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    364e:	00 00 

0000000000003650 <mlx_int_param_KeyRelease>:
    3650:	55                   	push   rbp
    3651:	31 c9                	xor    ecx,ecx
    3653:	53                   	push   rbx
    3654:	48 83 ec 08          	sub    rsp,0x8
    3658:	0f b6 76 54          	movzx  esi,BYTE PTR [rsi+0x54]
    365c:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    365f:	48 8b 9a 98 00 00 00 	mov    rbx,QWORD PTR [rdx+0x98]
    3666:	48 8b aa a0 00 00 00 	mov    rbp,QWORD PTR [rdx+0xa0]
    366d:	31 d2                	xor    edx,edx
    366f:	e8 7c ea ff ff       	call   20f0 <XkbKeycodeToKeysym@plt>
    3674:	48 83 c4 08          	add    rsp,0x8
    3678:	48 89 c7             	mov    rdi,rax
    367b:	48 89 ee             	mov    rsi,rbp
    367e:	48 89 d9             	mov    rcx,rbx
    3681:	31 c0                	xor    eax,eax
    3683:	5b                   	pop    rbx
    3684:	5d                   	pop    rbp
    3685:	ff e1                	jmp    rcx
    3687:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    368e:	00 00 

0000000000003690 <mlx_int_param_Expose>:
    3690:	8b 46 38             	mov    eax,DWORD PTR [rsi+0x38]
    3693:	85 c0                	test   eax,eax
    3695:	75 19                	jne    36b0 <mlx_int_param_Expose+0x20>
    3697:	48 8b ba 78 01 00 00 	mov    rdi,QWORD PTR [rdx+0x178]
    369e:	31 c0                	xor    eax,eax
    36a0:	48 8b 92 70 01 00 00 	mov    rdx,QWORD PTR [rdx+0x170]
    36a7:	ff e2                	jmp    rdx
    36a9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    36b0:	c3                   	ret
    36b1:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    36b8:	00 00 00 
    36bb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

00000000000036c0 <mlx_int_set_win_event_mask>:
    36c0:	41 55                	push   r13
    36c2:	49 89 fd             	mov    r13,rdi
    36c5:	41 54                	push   r12
    36c7:	55                   	push   rbp
    36c8:	48 bd 00 00 00 00 ff 	movabs rbp,0xffffffff00000000
    36cf:	ff ff ff 
    36d2:	53                   	push   rbx
    36d3:	48 81 ec 18 01 00 00 	sub    rsp,0x118
    36da:	48 8b 5f 30          	mov    rbx,QWORD PTR [rdi+0x30]
    36de:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    36e5:	00 00 
    36e7:	48 89 84 24 08 01 00 	mov    QWORD PTR [rsp+0x108],rax
    36ee:	00 
    36ef:	31 c0                	xor    eax,eax
    36f1:	4c 8d a4 24 90 00 00 	lea    r12,[rsp+0x90]
    36f8:	00 
    36f9:	48 85 db             	test   rbx,rbx
    36fc:	0f 84 ec 03 00 00    	je     3aee <mlx_int_set_win_event_mask+0x42e>
    3702:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    3708:	8b 83 78 03 00 00    	mov    eax,DWORD PTR [rbx+0x378]
    370e:	8b 93 90 03 00 00    	mov    edx,DWORD PTR [rbx+0x390]
    3714:	66 0f ef ed          	pxor   xmm5,xmm5
    3718:	4c 89 e1             	mov    rcx,r12
    371b:	0f 29 2c 24          	movaps XMMWORD PTR [rsp],xmm5
    371f:	66 0f 6f cd          	movdqa xmm1,xmm5
    3723:	66 0f 6f d5          	movdqa xmm2,xmm5
    3727:	48 c1 e0 20          	shl    rax,0x20
    372b:	0f 29 6c 24 10       	movaps XMMWORD PTR [rsp+0x10],xmm5
    3730:	48 09 c2             	or     rdx,rax
    3733:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
    3738:	0f 29 6c 24 20       	movaps XMMWORD PTR [rsp+0x20],xmm5
    373d:	48 89 14 24          	mov    QWORD PTR [rsp],rdx
    3741:	8b 93 60 03 00 00    	mov    edx,DWORD PTR [rbx+0x360]
    3747:	48 21 e8             	and    rax,rbp
    374a:	0f 29 6c 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm5
    374f:	48 09 d0             	or     rax,rdx
    3752:	8b 93 48 03 00 00    	mov    edx,DWORD PTR [rbx+0x348]
    3758:	89 c0                	mov    eax,eax
    375a:	48 c1 e2 20          	shl    rdx,0x20
    375e:	48 09 d0             	or     rax,rdx
    3761:	8b 93 30 03 00 00    	mov    edx,DWORD PTR [rbx+0x330]
    3767:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
    376c:	8b 83 18 03 00 00    	mov    eax,DWORD PTR [rbx+0x318]
    3772:	48 c1 e0 20          	shl    rax,0x20
    3776:	48 09 c2             	or     rdx,rax
    3779:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
    377e:	48 89 54 24 10       	mov    QWORD PTR [rsp+0x10],rdx
    3783:	8b 93 00 03 00 00    	mov    edx,DWORD PTR [rbx+0x300]
    3789:	48 21 e8             	and    rax,rbp
    378c:	48 09 d0             	or     rax,rdx
    378f:	8b 93 e8 02 00 00    	mov    edx,DWORD PTR [rbx+0x2e8]
    3795:	89 c0                	mov    eax,eax
    3797:	48 c1 e2 20          	shl    rdx,0x20
    379b:	48 09 d0             	or     rax,rdx
    379e:	8b 93 d0 02 00 00    	mov    edx,DWORD PTR [rbx+0x2d0]
    37a4:	48 89 44 24 18       	mov    QWORD PTR [rsp+0x18],rax
    37a9:	8b 83 b8 02 00 00    	mov    eax,DWORD PTR [rbx+0x2b8]
    37af:	48 c1 e0 20          	shl    rax,0x20
    37b3:	48 09 c2             	or     rdx,rax
    37b6:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
    37bb:	48 89 54 24 20       	mov    QWORD PTR [rsp+0x20],rdx
    37c0:	8b 93 a0 02 00 00    	mov    edx,DWORD PTR [rbx+0x2a0]
    37c6:	48 21 e8             	and    rax,rbp
    37c9:	48 09 d0             	or     rax,rdx
    37cc:	8b 93 88 02 00 00    	mov    edx,DWORD PTR [rbx+0x288]
    37d2:	89 c0                	mov    eax,eax
    37d4:	48 c1 e2 20          	shl    rdx,0x20
    37d8:	48 09 d0             	or     rax,rdx
    37db:	8b 93 70 02 00 00    	mov    edx,DWORD PTR [rbx+0x270]
    37e1:	48 89 44 24 28       	mov    QWORD PTR [rsp+0x28],rax
    37e6:	8b 83 58 02 00 00    	mov    eax,DWORD PTR [rbx+0x258]
    37ec:	48 c1 e0 20          	shl    rax,0x20
    37f0:	48 09 c2             	or     rdx,rax
    37f3:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
    37f8:	48 89 54 24 30       	mov    QWORD PTR [rsp+0x30],rdx
    37fd:	8b 93 40 02 00 00    	mov    edx,DWORD PTR [rbx+0x240]
    3803:	48 21 e8             	and    rax,rbp
    3806:	48 09 d0             	or     rax,rdx
    3809:	8b 93 28 02 00 00    	mov    edx,DWORD PTR [rbx+0x228]
    380f:	89 c0                	mov    eax,eax
    3811:	48 c1 e2 20          	shl    rdx,0x20
    3815:	48 09 d0             	or     rax,rdx
    3818:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
    381d:	0f 29 6c 24 40       	movaps XMMWORD PTR [rsp+0x40],xmm5
    3822:	8b 83 f8 01 00 00    	mov    eax,DWORD PTR [rbx+0x1f8]
    3828:	8b 93 10 02 00 00    	mov    edx,DWORD PTR [rbx+0x210]
    382e:	0f 29 6c 24 50       	movaps XMMWORD PTR [rsp+0x50],xmm5
    3833:	48 c1 e0 20          	shl    rax,0x20
    3837:	0f 29 6c 24 60       	movaps XMMWORD PTR [rsp+0x60],xmm5
    383c:	48 09 c2             	or     rdx,rax
    383f:	48 8b 44 24 48       	mov    rax,QWORD PTR [rsp+0x48]
    3844:	0f 29 6c 24 70       	movaps XMMWORD PTR [rsp+0x70],xmm5
    3849:	48 89 54 24 40       	mov    QWORD PTR [rsp+0x40],rdx
    384e:	8b 93 e0 01 00 00    	mov    edx,DWORD PTR [rbx+0x1e0]
    3854:	48 21 e8             	and    rax,rbp
    3857:	0f 29 ac 24 80 00 00 	movaps XMMWORD PTR [rsp+0x80],xmm5
    385e:	00 
    385f:	48 09 d0             	or     rax,rdx
    3862:	8b 93 c8 01 00 00    	mov    edx,DWORD PTR [rbx+0x1c8]
    3868:	89 c0                	mov    eax,eax
    386a:	48 c1 e2 20          	shl    rdx,0x20
    386e:	48 09 d0             	or     rax,rdx
    3871:	8b 93 b0 01 00 00    	mov    edx,DWORD PTR [rbx+0x1b0]
    3877:	48 89 44 24 48       	mov    QWORD PTR [rsp+0x48],rax
    387c:	8b 83 98 01 00 00    	mov    eax,DWORD PTR [rbx+0x198]
    3882:	48 c1 e0 20          	shl    rax,0x20
    3886:	48 09 c2             	or     rdx,rax
    3889:	48 8b 44 24 58       	mov    rax,QWORD PTR [rsp+0x58]
    388e:	48 89 54 24 50       	mov    QWORD PTR [rsp+0x50],rdx
    3893:	8b 93 80 01 00 00    	mov    edx,DWORD PTR [rbx+0x180]
    3899:	48 21 e8             	and    rax,rbp
    389c:	48 09 d0             	or     rax,rdx
    389f:	8b 93 68 01 00 00    	mov    edx,DWORD PTR [rbx+0x168]
    38a5:	89 c0                	mov    eax,eax
    38a7:	48 c1 e2 20          	shl    rdx,0x20
    38ab:	48 09 d0             	or     rax,rdx
    38ae:	8b 93 50 01 00 00    	mov    edx,DWORD PTR [rbx+0x150]
    38b4:	48 89 44 24 58       	mov    QWORD PTR [rsp+0x58],rax
    38b9:	8b 83 38 01 00 00    	mov    eax,DWORD PTR [rbx+0x138]
    38bf:	48 c1 e0 20          	shl    rax,0x20
    38c3:	48 09 c2             	or     rdx,rax
    38c6:	48 8b 44 24 68       	mov    rax,QWORD PTR [rsp+0x68]
    38cb:	48 89 54 24 60       	mov    QWORD PTR [rsp+0x60],rdx
    38d0:	8b 93 20 01 00 00    	mov    edx,DWORD PTR [rbx+0x120]
    38d6:	48 21 e8             	and    rax,rbp
    38d9:	48 09 d0             	or     rax,rdx
    38dc:	8b 93 08 01 00 00    	mov    edx,DWORD PTR [rbx+0x108]
    38e2:	89 c0                	mov    eax,eax
    38e4:	48 c1 e2 20          	shl    rdx,0x20
    38e8:	48 09 d0             	or     rax,rdx
    38eb:	8b 93 f0 00 00 00    	mov    edx,DWORD PTR [rbx+0xf0]
    38f1:	48 89 44 24 68       	mov    QWORD PTR [rsp+0x68],rax
    38f6:	8b 83 d8 00 00 00    	mov    eax,DWORD PTR [rbx+0xd8]
    38fc:	48 c1 e0 20          	shl    rax,0x20
    3900:	48 09 c2             	or     rdx,rax
    3903:	48 8b 44 24 78       	mov    rax,QWORD PTR [rsp+0x78]
    3908:	48 89 54 24 70       	mov    QWORD PTR [rsp+0x70],rdx
    390d:	8b 93 c0 00 00 00    	mov    edx,DWORD PTR [rbx+0xc0]
    3913:	48 21 e8             	and    rax,rbp
    3916:	48 09 d0             	or     rax,rdx
    3919:	8b 93 a8 00 00 00    	mov    edx,DWORD PTR [rbx+0xa8]
    391f:	89 c0                	mov    eax,eax
    3921:	48 c1 e2 20          	shl    rdx,0x20
    3925:	48 09 d0             	or     rax,rdx
    3928:	48 89 44 24 78       	mov    QWORD PTR [rsp+0x78],rax
    392d:	8b 93 90 00 00 00    	mov    edx,DWORD PTR [rbx+0x90]
    3933:	66 0f 66 4c 24 10    	pcmpgtd xmm1,XMMWORD PTR [rsp+0x10]
    3939:	66 0f 6f 5c 24 10    	movdqa xmm3,XMMWORD PTR [rsp+0x10]
    393f:	66 0f 6f 44 24 10    	movdqa xmm0,XMMWORD PTR [rsp+0x10]
    3945:	66 0f 6f 24 24       	movdqa xmm4,XMMWORD PTR [rsp]
    394a:	8b 43 78             	mov    eax,DWORD PTR [rbx+0x78]
    394d:	66 0f 62 d9          	punpckldq xmm3,xmm1
    3951:	66 0f 6a c1          	punpckhdq xmm0,xmm1
    3955:	66 0f 6f 0c 24       	movdqa xmm1,XMMWORD PTR [rsp]
    395a:	66 0f eb c3          	por    xmm0,xmm3
    395e:	66 0f 6f dd          	movdqa xmm3,xmm5
    3962:	48 c1 e0 20          	shl    rax,0x20
    3966:	66 0f 66 1c 24       	pcmpgtd xmm3,XMMWORD PTR [rsp]
    396b:	48 09 c2             	or     rdx,rax
    396e:	48 8b 84 24 88 00 00 	mov    rax,QWORD PTR [rsp+0x88]
    3975:	00 
    3976:	48 89 94 24 80 00 00 	mov    QWORD PTR [rsp+0x80],rdx
    397d:	00 
    397e:	8b 53 60             	mov    edx,DWORD PTR [rbx+0x60]
    3981:	48 21 e8             	and    rax,rbp
    3984:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3988:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    398c:	66 0f 6f dd          	movdqa xmm3,xmm5
    3990:	48 09 d0             	or     rax,rdx
    3993:	66 0f 66 5c 24 20    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x20]
    3999:	66 0f eb cc          	por    xmm1,xmm4
    399d:	8b 53 48             	mov    edx,DWORD PTR [rbx+0x48]
    39a0:	89 c0                	mov    eax,eax
    39a2:	66 0f 6f 64 24 20    	movdqa xmm4,XMMWORD PTR [rsp+0x20]
    39a8:	66 0f eb c1          	por    xmm0,xmm1
    39ac:	66 0f 6f 4c 24 20    	movdqa xmm1,XMMWORD PTR [rsp+0x20]
    39b2:	48 c1 e2 20          	shl    rdx,0x20
    39b6:	66 0f 62 e3          	punpckldq xmm4,xmm3
    39ba:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    39be:	66 0f 6f dd          	movdqa xmm3,xmm5
    39c2:	48 09 d0             	or     rax,rdx
    39c5:	66 0f 66 5c 24 30    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x30]
    39cb:	66 0f eb cc          	por    xmm1,xmm4
    39cf:	66 0f 6f 64 24 30    	movdqa xmm4,XMMWORD PTR [rsp+0x30]
    39d5:	48 89 84 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rax
    39dc:	00 
    39dd:	ba 00 08 00 00       	mov    edx,0x800
    39e2:	66 0f 66 94 24 80 00 	pcmpgtd xmm2,XMMWORD PTR [rsp+0x80]
    39e9:	00 00 
    39eb:	66 0f 62 e3          	punpckldq xmm4,xmm3
    39ef:	66 0f eb cc          	por    xmm1,xmm4
    39f3:	66 0f 6f e5          	movdqa xmm4,xmm5
    39f7:	66 0f eb c1          	por    xmm0,xmm1
    39fb:	66 0f 6f 4c 24 30    	movdqa xmm1,XMMWORD PTR [rsp+0x30]
    3a01:	66 0f 66 64 24 40    	pcmpgtd xmm4,XMMWORD PTR [rsp+0x40]
    3a07:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3a0b:	66 0f 6f 5c 24 40    	movdqa xmm3,XMMWORD PTR [rsp+0x40]
    3a11:	66 0f 62 dc          	punpckldq xmm3,xmm4
    3a15:	66 0f eb d9          	por    xmm3,xmm1
    3a19:	66 0f 6f 4c 24 40    	movdqa xmm1,XMMWORD PTR [rsp+0x40]
    3a1f:	66 0f 6a cc          	punpckhdq xmm1,xmm4
    3a23:	66 0f 6f 64 24 50    	movdqa xmm4,XMMWORD PTR [rsp+0x50]
    3a29:	66 0f eb cb          	por    xmm1,xmm3
    3a2d:	66 0f 6f dd          	movdqa xmm3,xmm5
    3a31:	66 0f 66 5c 24 50    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x50]
    3a37:	66 0f eb c1          	por    xmm0,xmm1
    3a3b:	66 0f 6f 4c 24 50    	movdqa xmm1,XMMWORD PTR [rsp+0x50]
    3a41:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3a45:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3a49:	66 0f 6f dd          	movdqa xmm3,xmm5
    3a4d:	66 0f 66 5c 24 60    	pcmpgtd xmm3,XMMWORD PTR [rsp+0x60]
    3a53:	66 0f eb cc          	por    xmm1,xmm4
    3a57:	66 0f 6f 64 24 60    	movdqa xmm4,XMMWORD PTR [rsp+0x60]
    3a5d:	66 0f 62 e3          	punpckldq xmm4,xmm3
    3a61:	66 0f eb cc          	por    xmm1,xmm4
    3a65:	66 0f 6f e5          	movdqa xmm4,xmm5
    3a69:	66 0f eb c1          	por    xmm0,xmm1
    3a6d:	66 0f 6f 4c 24 60    	movdqa xmm1,XMMWORD PTR [rsp+0x60]
    3a73:	66 0f 66 64 24 70    	pcmpgtd xmm4,XMMWORD PTR [rsp+0x70]
    3a79:	66 0f 6a cb          	punpckhdq xmm1,xmm3
    3a7d:	66 0f 6f 5c 24 70    	movdqa xmm3,XMMWORD PTR [rsp+0x70]
    3a83:	66 0f 62 dc          	punpckldq xmm3,xmm4
    3a87:	66 0f eb d9          	por    xmm3,xmm1
    3a8b:	66 0f 6f 4c 24 70    	movdqa xmm1,XMMWORD PTR [rsp+0x70]
    3a91:	66 0f 6a cc          	punpckhdq xmm1,xmm4
    3a95:	66 0f eb cb          	por    xmm1,xmm3
    3a99:	66 0f 6f 9c 24 80 00 	movdqa xmm3,XMMWORD PTR [rsp+0x80]
    3aa0:	00 00 
    3aa2:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
    3aa5:	66 0f eb c1          	por    xmm0,xmm1
    3aa9:	49 8b 7d 00          	mov    rdi,QWORD PTR [r13+0x0]
    3aad:	66 0f 6f 8c 24 80 00 	movdqa xmm1,XMMWORD PTR [rsp+0x80]
    3ab4:	00 00 
    3ab6:	66 0f 62 da          	punpckldq xmm3,xmm2
    3aba:	66 0f 6a ca          	punpckhdq xmm1,xmm2
    3abe:	66 0f eb cb          	por    xmm1,xmm3
    3ac2:	66 0f eb c1          	por    xmm0,xmm1
    3ac6:	66 0f 6f c8          	movdqa xmm1,xmm0
    3aca:	66 0f 73 d9 08       	psrldq xmm1,0x8
    3acf:	66 0f eb c1          	por    xmm0,xmm1
    3ad3:	66 0f d6 84 24 d8 00 	movq   QWORD PTR [rsp+0xd8],xmm0
    3ada:	00 00 
    3adc:	e8 7f e8 ff ff       	call   2360 <XChangeWindowAttributes@plt>
    3ae1:	48 8b 5b 10          	mov    rbx,QWORD PTR [rbx+0x10]
    3ae5:	48 85 db             	test   rbx,rbx
    3ae8:	0f 85 1a fc ff ff    	jne    3708 <mlx_int_set_win_event_mask+0x48>
    3aee:	48 8b 84 24 08 01 00 	mov    rax,QWORD PTR [rsp+0x108]
    3af5:	00 
    3af6:	64 48 2b 04 25 28 00 	sub    rax,QWORD PTR fs:0x28
    3afd:	00 00 
    3aff:	75 10                	jne    3b11 <mlx_int_set_win_event_mask+0x451>
    3b01:	48 81 c4 18 01 00 00 	add    rsp,0x118
    3b08:	31 c0                	xor    eax,eax
    3b0a:	5b                   	pop    rbx
    3b0b:	5d                   	pop    rbp
    3b0c:	41 5c                	pop    r12
    3b0e:	41 5d                	pop    r13
    3b10:	c3                   	ret
    3b11:	e8 2a e7 ff ff       	call   2240 <__stack_chk_fail@plt>
    3b16:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    3b1d:	00 00 00 

0000000000003b20 <mlx_hook>:
    3b20:	48 63 f6             	movsxd rsi,esi
    3b23:	48 8d 04 76          	lea    rax,[rsi+rsi*2]
    3b27:	48 8d 04 c7          	lea    rax,[rdi+rax*8]
    3b2b:	48 89 48 50          	mov    QWORD PTR [rax+0x50],rcx
    3b2f:	4c 89 40 58          	mov    QWORD PTR [rax+0x58],r8
    3b33:	89 50 48             	mov    DWORD PTR [rax+0x48],edx
    3b36:	c3                   	ret
    3b37:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
    3b3e:	00 00 

0000000000003b40 <mlx_do_key_autorepeatoff>:
    3b40:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3b43:	e9 28 e5 ff ff       	jmp    2070 <XAutoRepeatOff@plt>
    3b48:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    3b4f:	00 

0000000000003b50 <mlx_do_key_autorepeaton>:
    3b50:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3b53:	e9 b8 e5 ff ff       	jmp    2110 <XAutoRepeatOn@plt>
    3b58:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
    3b5f:	00 

0000000000003b60 <mlx_do_sync>:
    3b60:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3b63:	31 f6                	xor    esi,esi
    3b65:	e9 c6 e6 ff ff       	jmp    2230 <XSync@plt>
    3b6a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000003b70 <mlx_destroy_display>:
    3b70:	48 8b 3f             	mov    rdi,QWORD PTR [rdi]
    3b73:	e9 f8 e5 ff ff       	jmp    2170 <XCloseDisplay@plt>
