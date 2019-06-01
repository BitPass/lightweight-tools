.data				; Monstrously fast brightness algorithm
				; 3-6x speedup to managed C++

.code

ASMAdjustBrightness proc	
	mov r10, 0
	cmp r8w, 0
	jl SubtractBrightness

	mov r11w, 0fffh			

MainLoopAdd:
	mov al, byte ptr [rdx + r10]
	add al, r8b 		
	cmovc ax, r11w		
	mov byte ptr[rcx + r10], al	
	inc r10			
	dec r9d				
	jnz MainLoopAdd			
	ret				

SubtractBrightness:
	mov r11w, 0			
	neg r8w, 			
	

MainLoopSubtract
	mov al, byte ptr [rdx + r10]	
	sub al, r8b 			
	cmovc ax, r11w			
	mov byte ptr[rcx + r10], al	
	inc r10				
	dec r9d				
	jnz MainLoopSubtract		
	ret				

ASMAdjustBrightness endp
end