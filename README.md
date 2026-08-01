# Elyamany OS (اليماني او اس)

Elyamany OS — مشروع نظام تشغيل تعليمي/تجريبي.

الشعار: شعر الحصان

هذا المستودع يحتوي على سقالة مشروع لنظام تشغيل باسم Elyamany OS (اليماني او اس).

الحالة الحالية: أضفت هيكل المجلدات وملفات نمطية (stubs) لجميع المكونات المطلوبة كما طُلِبَت.

ما تم إضافته (موجز):
- boot/ (قوالب limine/grub/asm/linker)
- kernel/ (ملفات نواة C++ نمطية)
- arch/ (مجلدات x86/x86_64/arm/arm64 مع README)
- memory/, process/, interrupt/, drivers/, graphics/, filesystem/, shell/, network/, security/, services/, installer/, recovery/, iso/, packages/
- toolchain/, build/scripts/, rootfs/ هيكل

ملاحظة مهمة:
- لم أُدرج ملفات ثنائية مثل BOOTX64.EFI الحقيقية أو محمل UEFI جاهز — أضفت ملف نصّي يشرح كيفية إدراجها.
- هذه ملفات نمطية (stubs) لتنظيم العمل. تتطلب كل وحدة تنفيذية حقيقية، أداة بناء عبر-المترجم (cross-compiler)، واعتبارات أمان/ترخيص.

الأوامر المقترحة للبدء بالبناء (تحتاج للتخصيص):
```bash
# تبديل إلى الفرع الجديد
git checkout elyamany-os-scaffold
# تنفيذ السكريبت التجريبي لبناء الصورة
bash build/scripts/build.sh
```
