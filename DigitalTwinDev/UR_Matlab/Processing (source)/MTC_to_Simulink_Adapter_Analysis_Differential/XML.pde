void printXML(XML doc) {
  printXML(doc, 2);
}

void printXML(XML doc, int indent) {
  println(doc.format(indent));
}

XML findElementWithAttributeValue(XML[] elements, String attrName, String attrValue) {
  if (elements == null || attrName == null || attrValue == null) return null;
  for (XML x : elements) {
    if (x.hasAttribute(attrName) && attrValue.equals(x.getString(attrName))) {
      return x;
    }
  }
  return null;
}

XML nonNullXML(XML maybe) {
  if (maybe == null) return parseXML("<empty></empty>");
  return maybe;
}
