#include "dom_utils.hpp"
#include <string>

using namespace emscripten;

namespace dom {
    val domUtils::createElement(const std::string& tag, const std::string& id, val parent) {
        val document = val::global("document");
        
        // IDが指定されており、既に要素が存在する場合はその要素を返す
        if (!id.empty()) {
            val existingEl = document.call<val>("getElementById", val(id));
            if (!existingEl.isNull() && !existingEl.isUndefined()) {
                return existingEl;
            }
        }

        val el = document.call<val>("createElement", val(tag));
        if (!id.empty()) {
            el.set("id", val(id));
        }
        
        parent.call<void>("appendChild", el);
        return el;
    }

    void domUtils::injectStyle(const std::string& url) {
        val document = val::global("document");
        val link = document.call<val>("createElement", val("link"));
        link.set("rel", val("stylesheet"));
        link.set("href", val(url));
        document["head"].call<void>("appendChild", link);
    }

    void domUtils::setAttribute(val element, const std::string& attr, const std::string& value) {
        element.call<void>("setAttribute", val(attr), val(value));
    }

    void domUtils::removeElement(const std::string& id) {
        val document = val::global("document");
        val el = document.call<val>("getElementById", val(id));
        if (!el.isNull() && !el.isUndefined()) {
            el.call<void>("remove");
        }
    }

    void domUtils::setText(val element, const std::string& text) {
        element.set("textContent", val(text));
    }

    void domUtils::AdDescElementCreate(emscripten::val currentAdData) {
        val detailsContainer = dom::domUtils::createElement("div", "details-container");
        val detailsBtn = dom::domUtils::createElement("button", "detailsButton", detailsContainer);
        val detailsSpan = dom::domUtils::createElement("span", "detailsButtonInline", detailsBtn);
        dom::domUtils::setText(detailsSpan, "詳細を開く");

        val sponsor = dom::domUtils::createElement("div", "sponsor-container");
        val sponsorRow = dom::domUtils::createElement("p", "sponsor-row", sponsor);
        val sponsorInline = dom::domUtils::createElement("span", "sponsor-inline", sponsorRow);
        dom::domUtils::setText(sponsorInline, "スポンサー提供: " + currentAdData["publisher"].as<std::string>());
        
        detailsBtn.set("onclick", val::module_property("onDetailsClick"));

        val skipBtn = dom::domUtils::createElement("button", "skipAdButton");
        val skipBtnInline = dom::domUtils::createElement("span", "skipAdButtonInline", skipBtn);
        skipBtn.set("disabled", true);
    }
}