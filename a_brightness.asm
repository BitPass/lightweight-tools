;       64-bit CPU-based smooth brightness adjuster
;       3-6x speedup over managed C++
;       based on whatsacreel's youtube tutorial x64 Assembly and C++ Tutorial 25
;
;       void ASMAdjustBrightness(
;       unsigned char* bmpDataScan0,    = RCX
;       unsigned char* bmpOriginal,     = RDX
;       short value,(added)             = R8W
;       int imageSizeInBytes            = R9D

.data

.code

ASMAdjustBrightness proc	
	mov r10, 0
	cmp r8w, 0
	jl SubtractBrightness
	mov r11w, 0fffh                     ; 255 for overflow

MainLoopAdd:
	mov al, byte ptr [rdx + r10]        ; read byte from original image
	add al, r8b                         ; add brightness
	cmovc ax, r11w                      ; set to 255 on overflow
	mov byte ptr[rcx + r10], al         ; store the answer in scan0
	inc r10                             ; move to the next byte in the arrays
	dec r9d                             ; decrememnt our counter
	jnz MainLoopAdd                     ; jump if there's more
	ret	                                ; return to c++

SubtractBrightness:
	mov r11w, 0			                ; move 0 into the underflow
	neg r8w, 			                ; negate the value we're subbing
	

MainLoopSubtract
	mov al, byte ptr [rdx + r10]	    ; read byte from original image
	sub al, r8b 			            ; sub the brightness
	cmovc ax, r11w			            ; set to 255 on overflow
	mov byte ptr[rcx + r10], al         ; store the answer in scan0
	inc r10				                ; move to the next byte in the arrays
	dec r9d				                ; decrememnt our counter
	jnz MainLoopSubtract		        ; jump if there's more
	ret				                    ; return to c++

ASMAdjustBrightness endp
end
