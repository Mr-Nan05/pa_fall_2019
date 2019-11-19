
elf.o：     文件格式 elf32-i386


Disassembly of section .text:

00000000 <loader>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	53                   	push   %ebx
   4:	83 ec 14             	sub    $0x14,%esp
   7:	e8 fc ff ff ff       	call   8 <loader+0x8>
   c:	81 c3 02 00 00 00    	add    $0x2,%ebx
  12:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  19:	8d 83 4c 00 00 00    	lea    0x4c(%ebx),%eax
  1f:	50                   	push   %eax
  20:	6a 1d                	push   $0x1d
  22:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
  28:	50                   	push   %eax
  29:	8d 83 10 00 00 00    	lea    0x10(%ebx),%eax
  2f:	50                   	push   %eax
  30:	e8 fc ff ff ff       	call   31 <loader+0x31>
  35:	83 c4 10             	add    $0x10,%esp
  38:	8b 45 f0             	mov    -0x10(%ebp),%eax
  3b:	8b 50 1c             	mov    0x1c(%eax),%edx
  3e:	8b 45 f0             	mov    -0x10(%ebp),%eax
  41:	01 d0                	add    %edx,%eax
  43:	89 45 f4             	mov    %eax,-0xc(%ebp)
  46:	8b 45 f0             	mov    -0x10(%ebp),%eax
  49:	8b 40 2c             	mov    0x2c(%eax),%eax
  4c:	0f b7 c0             	movzwl %ax,%eax
  4f:	c1 e0 05             	shl    $0x5,%eax
  52:	89 c2                	mov    %eax,%edx
  54:	8b 45 f4             	mov    -0xc(%ebp),%eax
  57:	01 d0                	add    %edx,%eax
  59:	89 45 ec             	mov    %eax,-0x14(%ebp)
  5c:	eb 5b                	jmp    b9 <loader+0xb9>
  5e:	8b 45 f4             	mov    -0xc(%ebp),%eax
  61:	8b 00                	mov    (%eax),%eax
  63:	83 f8 01             	cmp    $0x1,%eax
  66:	75 4d                	jne    b5 <loader+0xb5>
  68:	8b 45 f4             	mov    -0xc(%ebp),%eax
  6b:	8b 40 14             	mov    0x14(%eax),%eax
  6e:	8b 55 f4             	mov    -0xc(%ebp),%edx
  71:	8b 52 04             	mov    0x4(%edx),%edx
  74:	89 d1                	mov    %edx,%ecx
  76:	8b 55 f4             	mov    -0xc(%ebp),%edx
  79:	8b 52 08             	mov    0x8(%edx),%edx
  7c:	83 ec 04             	sub    $0x4,%esp
  7f:	50                   	push   %eax
  80:	51                   	push   %ecx
  81:	52                   	push   %edx
  82:	e8 fc ff ff ff       	call   83 <loader+0x83>
  87:	83 c4 10             	add    $0x10,%esp
  8a:	8b 45 f4             	mov    -0xc(%ebp),%eax
  8d:	8b 50 14             	mov    0x14(%eax),%edx
  90:	8b 45 f4             	mov    -0xc(%ebp),%eax
  93:	8b 40 10             	mov    0x10(%eax),%eax
  96:	29 c2                	sub    %eax,%edx
  98:	8b 45 f4             	mov    -0xc(%ebp),%eax
  9b:	8b 48 10             	mov    0x10(%eax),%ecx
  9e:	8b 45 f4             	mov    -0xc(%ebp),%eax
  a1:	8b 40 08             	mov    0x8(%eax),%eax
  a4:	01 c8                	add    %ecx,%eax
  a6:	83 ec 04             	sub    $0x4,%esp
  a9:	52                   	push   %edx
  aa:	6a 00                	push   $0x0
  ac:	50                   	push   %eax
  ad:	e8 fc ff ff ff       	call   ae <loader+0xae>
  b2:	83 c4 10             	add    $0x10,%esp
  b5:	83 45 f4 20          	addl   $0x20,-0xc(%ebp)
  b9:	8b 45 f4             	mov    -0xc(%ebp),%eax
  bc:	3b 45 ec             	cmp    -0x14(%ebp),%eax
  bf:	72 9d                	jb     5e <loader+0x5e>
  c1:	8b 45 f0             	mov    -0x10(%ebp),%eax
  c4:	8b 40 18             	mov    0x18(%eax),%eax
  c7:	89 45 e8             	mov    %eax,-0x18(%ebp)
  ca:	8b 45 e8             	mov    -0x18(%ebp),%eax
  cd:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  d0:	c9                   	leave  
  d1:	c3                   	ret    

Disassembly of section .text.__x86.get_pc_thunk.bx:

00000000 <__x86.get_pc_thunk.bx>:
   0:	8b 1c 24             	mov    (%esp),%ebx
   3:	c3                   	ret    
