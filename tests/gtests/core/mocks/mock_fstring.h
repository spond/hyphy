class Mock_FString : public _FString {
 public:
  MOCK_METHOD0(makeDynamic,
      BaseRef(void));
  MOCK_METHOD1(Duplicate,
      void(BaseRef));
  MOCK_METHOD1(Add,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(AddOn,
      long(_PMathObj));
  MOCK_METHOD1(AreEqual,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(AreEqualCIS,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(Less,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(LessEq,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(Greater,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(GreaterEq,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(NotEqual,
      _PMathObj(_PMathObj));
  MOCK_METHOD0(RerootTree,
      _PMathObj(void));
  MOCK_METHOD1(EqualAmb,
      _PMathObj(_PMathObj));
  MOCK_METHOD2(EqualRegExp,
      _PMathObj(, ));
  MOCK_METHOD1(ReplaceReqExp,
      _PMathObj(_PMathObj));
  MOCK_METHOD0(CountGlobalObjects,
      _PMathObj(void));
  MOCK_METHOD0(FileExists,
      _PMathObj(void));
  MOCK_METHOD1(Evaluate,
      _PMathObj(_hyExecutionContext));
  MOCK_METHOD1(Join,
      _PMathObj(_PMathObj));
  MOCK_METHOD1(Differentiate,
      _PMathObj(_PMathObj));
  MOCK_METHOD0(ObjectClass,
      unsigned long(void));
  MOCK_METHOD0(Compute,
      _PMathObj(void));
  MOCK_METHOD1(MapStringToVector,
      _PMathObj(_PMathObj));
  MOCK_METHOD2(CharAccess,
      _PMathObj(_PMathObj, _PMathObj));
  MOCK_METHOD4(Execute,
      _PMathObj(long, _MathObject, _MathObject, _hyExecutionContext));
  MOCK_METHOD0(toStr,
      BaseRef(void));
  MOCK_METHOD0(IsVariable,
      bool(void));
  MOCK_METHOD0(HasChanged,
      bool(void));
  MOCK_METHOD0(IsEmpty,
      bool(void));
};
