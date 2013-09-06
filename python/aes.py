# -*- coding: utf-8 -*-

import hashlib
from Crypto.Cipher import AES

BS = 16
pad = lambda s: s + (BS - len(s) % BS) * chr(BS - len(s) % BS)
unpad = lambda s: s[0 : -ord(s[-1])]

class AESCipher:
    def __init__(self, key):
        key = hashlib.md5(key).digest()
        self.cipher = AES.new(key)

    def encrypt(self, raw):
        raw = pad(raw)
        return self.cipher.encrypt(raw)

    def decrypt(self, enc):
        return unpad(self.cipher.decrypt(enc))

