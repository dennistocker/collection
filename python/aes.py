# -*- coding: utf-8 -*-

import hashlib
from Crypto.Cipher import AES

class AESCipher:
    BS = 16
    def __init__(self, key):
        key = hashlib.md5(key).digest()
        self.cipher = AES.new(key)

    def _pad(self, s):
        pad = self.BS - len(s) % self.BS
        return s + chr(pad) * pad

    def _unpad(self, s):
        pad = s[-1]
        return s[:-ord(pad)]

    def encrypt(self, raw):
        raw = self._pad(raw)
        return self.cipher.encrypt(raw)

    def decrypt(self, enc):
        return self._unpad(self.cipher.decrypt(enc))

