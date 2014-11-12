JarkomThreadingSample
=====================

Contoh sederhana threading di C/C++ dengan menggunakan pthreads dan std::thread (khusus C++11)

Deskripsi permasalahan
----------------------
Terdapat sebuah produsen yang menghasilkan sebuah bilangan acak ke buffer setiap 0-999 ms.
Terdapat 3 buah konsumen yang mengambil bilangan dari buffer setiap 500 ms.
