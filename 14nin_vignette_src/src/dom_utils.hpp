#pragma once

#include <emscripten/val.h>

namespace dom {
    class domUtils {
        public:
            // 要素を作成し、親要素に追加する
            static emscripten::val createElement(const std::string& tag, const std::string& id = "", emscripten::val parent = emscripten::val::global("document")["body"]);
            
            // スタイルシート（linkタグ）をheadに追加する
            static void injectStyle(const std::string& url);
            
            // 要素に属性をセットする
            static void setAttribute(emscripten::val element, const std::string& attr, const std::string& value);
            
            // 要素を削除する
            static void removeElement(const std::string& id);

            // テキストコンテンツをセットする
            static void setText(emscripten::val element, const std::string& text);

            static void AdDescElementCreate(emscripten::val currentAdData);
    };
}