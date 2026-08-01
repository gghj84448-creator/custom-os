; startup.asm - placeholder
; هذا ملف تجريبي لبداية تشغيل التجميعة (العربية: محمل إقلاع ابتدائي)
; يجب استبداله بشيفرة محمل للإقلاع الحقيقي (MBR/GRUB/UEFI) عند الحاجة

BITS 16
ORG 0x7C00

start:
    cli
    hlt

TIMES 510-($-$$) db 0
DW 0xAA55
