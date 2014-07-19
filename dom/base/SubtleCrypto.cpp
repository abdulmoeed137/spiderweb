/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/SubtleCrypto.h"

#include "mozilla/dom/Promise.h"
#include "mozilla/dom/SubtleCryptoBinding.h"
#include "mozilla/dom/WebCryptoTask.h"

namespace mozilla {
namespace dom {

NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE(SubtleCrypto, mWindow)
NS_IMPL_CYCLE_COLLECTING_ADDREF(SubtleCrypto)
NS_IMPL_CYCLE_COLLECTING_RELEASE(SubtleCrypto)
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(SubtleCrypto)
  NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
  NS_INTERFACE_MAP_ENTRY(nsISupports)
NS_INTERFACE_MAP_END



SubtleCrypto::SubtleCrypto(nsPIDOMWindow* aWindow)
  : mWindow(aWindow)
{
  SetIsDOMBinding();
}

JSObject*
SubtleCrypto::WrapObject(JSContext* aCx)
{
  return SubtleCryptoBinding::Wrap(aCx, this);
}

#define SUBTLECRYPTO_METHOD_BODY(Operation, aRv, ...)                   \
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(mWindow);        \
  MOZ_ASSERT(global);                                                   \
  nsRefPtr<Promise> p = Promise::Create(global, aRv);                   \
  if (aRv.Failed()) {                                                   \
    return nullptr;                                                     \
  }                                                                     \
  nsRefPtr<WebCryptoTask> task = WebCryptoTask::Create ## Operation ## Task(__VA_ARGS__); \
  task->DispatchWithPromise(p); \
  return p.forget();

already_AddRefed<Promise>
SubtleCrypto::Encrypt(JSContext* cx,
                      const ObjectOrString& algorithm,
                      CryptoKey& key,
                      const CryptoOperationData& data,
                      ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(Encrypt, aRv, cx, algorithm, key, data)
}

already_AddRefed<Promise>
SubtleCrypto::Decrypt(JSContext* cx,
                      const ObjectOrString& algorithm,
                      CryptoKey& key,
                      const CryptoOperationData& data,
                      ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(Decrypt, aRv, cx, algorithm, key, data)
}

already_AddRefed<Promise>
SubtleCrypto::Sign(JSContext* cx,
                   const ObjectOrString& algorithm,
                   CryptoKey& key,
                   const CryptoOperationData& data,
                   ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(Sign, aRv, cx, algorithm, key, data)
}

already_AddRefed<Promise>
SubtleCrypto::Verify(JSContext* cx,
                     const ObjectOrString& algorithm,
                     CryptoKey& key,
                     const CryptoOperationData& signature,
                     const CryptoOperationData& data,
                     ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(Verify, aRv, cx, algorithm, key, signature, data)
}

already_AddRefed<Promise>
SubtleCrypto::Digest(JSContext* cx,
                     const ObjectOrString& algorithm,
                     const CryptoOperationData& data,
                     ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(Digest, aRv, cx, algorithm, data)
}


already_AddRefed<Promise>
SubtleCrypto::ImportKey(JSContext* cx,
                        const nsAString& format,
                        const KeyData& keyData,
                        const ObjectOrString& algorithm,
                        bool extractable,
                        const Sequence<nsString>& keyUsages,
                        ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(ImportKey, aRv, cx, format, keyData, algorithm,
                           extractable, keyUsages)
}

already_AddRefed<Promise>
SubtleCrypto::ExportKey(const nsAString& format,
                        CryptoKey& key,
                        ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(ExportKey, aRv, format, key)
}

already_AddRefed<Promise>
SubtleCrypto::GenerateKey(JSContext* cx, const ObjectOrString& algorithm,
                          bool extractable, const Sequence<nsString>& keyUsages,
                          ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(GenerateKey, aRv, cx, algorithm, extractable, keyUsages)
}

already_AddRefed<Promise>
SubtleCrypto::DeriveKey(JSContext* cx,
                        const ObjectOrString& algorithm,
                        CryptoKey& baseKey,
                        const ObjectOrString& derivedKeyType,
                        bool extractable, const Sequence<nsString>& keyUsages,
                        ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(DeriveKey, aRv, cx, algorithm, baseKey,
                           derivedKeyType, extractable, keyUsages)
}

already_AddRefed<Promise>
SubtleCrypto::DeriveBits(JSContext* cx,
                         const ObjectOrString& algorithm,
                         CryptoKey& baseKey,
                         uint32_t length,
                         ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(DeriveBits, aRv, cx, algorithm, baseKey, length)
}

already_AddRefed<Promise>
SubtleCrypto::WrapKey(JSContext* cx,
                      const nsAString& format,
                      CryptoKey& key,
                      CryptoKey& wrappingKey,
                      const ObjectOrString& wrapAlgorithm,
                      ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(WrapKey, aRv, cx, format, key, wrappingKey, wrapAlgorithm)
}

already_AddRefed<Promise>
SubtleCrypto::UnwrapKey(JSContext* cx,
                        const nsAString& format,
                        const ArrayBufferViewOrArrayBuffer& wrappedKey,
                        CryptoKey& unwrappingKey,
                        const ObjectOrString& unwrapAlgorithm,
                        const ObjectOrString& unwrappedKeyAlgorithm,
                        bool extractable,
                        const Sequence<nsString>& keyUsages,
                        ErrorResult& aRv)
{
  SUBTLECRYPTO_METHOD_BODY(UnwrapKey, aRv, cx, format, wrappedKey, unwrappingKey,
                           unwrapAlgorithm, unwrappedKeyAlgorithm,
                           extractable, keyUsages)
}

} // namespace dom
} // namespace mozilla
